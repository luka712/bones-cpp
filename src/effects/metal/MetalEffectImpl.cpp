#if USE_METAL




#include "effects/metal/MetalEffectImpl.hpp"
#include "texture/bns_metal_texture2d.hpp"
#include "bns_metal_util.hpp"
#include "bns_framework.hpp"
#include "buffer_layout/BufferLayoutData.hpp"

namespace bns
{
    MetalEffectImpl::MetalEffectImpl(const Framework &framework)
        : Effect(framework)
    {
        m_renderer = static_cast<MetalRenderer *>(framework.GetRenderer());
    }

    MTL::Buffer *MetalEffectImpl::CreateVertexBuffer()
    {
        std::vector<float> data = {
            // position, tex coords
            -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
            -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bottom left
            1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bottom right

            -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // top left
            1.0f, -1.0f, 0.0f, 1.0f, 1.0f, // bottom right
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f   // top right
        };

        MTL::Buffer *vertexBuffer = MetalUtil::Buffer.Create(m_device, data, "EffectVertexBuffer");

        return vertexBuffer;
    }

    MTL::RenderPipelineState *MetalEffectImpl::CreateRenderPipeline(MTL::Library *pLibrary, 
    std::string vertexFunctionName, std::string fragmentFunctionName, MTL::PixelFormat pixelFormat)
    {

        MTL::Function *pVertexFn = pLibrary->newFunction(NS::String::string(vertexFunctionName.c_str(), NS::StringEncoding::UTF8StringEncoding));
        MTL::Function *pFragFn = pLibrary->newFunction(NS::String::string(fragmentFunctionName.c_str(), NS::StringEncoding::UTF8StringEncoding));

        MTL::RenderPipelineDescriptor *pPipelineDescriptor = MetalUtil::RenderPipelineDescriptor.Create(pVertexFn, pFragFn);

        // BUFFERS
        BufferLayoutDescriptor bufferLayoutDescriptor;
        bufferLayoutDescriptor.Step = VertexStepMode::Vertex;
        bufferLayoutDescriptor.Stride = sizeof(f32) * 5;
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x4, 2, sizeof(f32) * 5});

        std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
        vertexBufferLayouts.push_back(bufferLayoutDescriptor);

        MetalVertexBufferLayoutAttributesDto layoutsAttributesDto = MetalUtil::VertexBufferLayout.Create(vertexBufferLayouts);

        // vertex
        MTL::VertexDescriptor *pVertexDesc = pPipelineDescriptor->vertexDescriptor();

        NS::UInteger i = 0;
        for (auto layout : layoutsAttributesDto.BufferLayouts)
        {
            pVertexDesc->layouts()->setObject(layout, i);
        }
        i = 0;
        for (auto attr : layoutsAttributesDto.BufferAttributes)
        {
            pVertexDesc->attributes()->setObject(attr, i);
        }

        // set pixel format
        MTL::RenderPipelineColorAttachmentDescriptor *colorAttachment = pPipelineDescriptor->colorAttachments()->object(NS::UInteger(0));
        colorAttachment->setPixelFormat(pixelFormat);

        colorAttachment->setBlendingEnabled(true);

        colorAttachment->setRgbBlendOperation(MTL::BlendOperationAdd);
        colorAttachment->setSourceRGBBlendFactor(MTL::BlendFactorSourceAlpha);
        colorAttachment->setDestinationRGBBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);

        colorAttachment->setAlphaBlendOperation(MTL::BlendOperationAdd);
        colorAttachment->setSourceAlphaBlendFactor(MTL::BlendFactorSourceAlpha);
        colorAttachment->setDestinationAlphaBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);

        NS::Error *pError = nullptr;
        m_pipeline = m_device->newRenderPipelineState(pPipelineDescriptor, &pError);
        if (!m_pipeline)
        {
            printf("%s", pError->localizedDescription()->utf8String());
            return nullptr;
        }

        pPipelineDescriptor->release();
        pFragFn->release();
        pVertexFn->release();

        return m_pipeline;
    };

   
    MTL::RenderPipelineState *MetalEffectImpl::CreateRenderPipeline()
    {

        FileLoader fileLoader;
        std::string shaderSource = fileLoader.LoadFile(GetShaderPath());

        MTL::Library *pLibrary = MetalUtil::Library.Create(m_device, shaderSource);

        m_pipeline = CreateRenderPipeline(pLibrary);

        pLibrary->release();

        return m_pipeline;
    };

     void MetalEffectImpl::Initialize()
    {
        m_device = m_renderer->GetDevice();

        Vec2i bufferSize = m_framework.GetRenderer()->GetBufferSize();
        Texture2D *texture = m_framework.GetTextureManager()
                                 .CreateEmpty(bufferSize.X, bufferSize.Y,
                                              TextureUsage::CopyDst_TextureBinding_RenderAttachment,
                                              TextureFormat::BGRA_8_Unorm);
        m_sourceTexture = static_cast<MetalTexture2D *>(texture);

        m_vertexBuffer = CreateVertexBuffer();
        m_pipeline = CreateRenderPipeline();
    }

    void MetalEffectImpl::Draw(void *destinationTexture)
    {
        MTL::CommandQueue *queue = m_renderer->GetCommandQueue();

        // Convert to Metal types
        MetalTexture2D *mtlTextureWrapper = static_cast<MetalTexture2D *>(m_sourceTexture);
        MTL::Texture *mtlDestTexture = static_cast<MTL::Texture *>(destinationTexture);

        MTL::CommandBuffer *commandBuffer = queue->commandBuffer();

        // Create a command pEncoder which can be used to submit GPU operations.
        MTL::RenderPassDescriptor *pRenderPassDesc = MTL::RenderPassDescriptor::renderPassDescriptor();

        MTL::RenderPassColorAttachmentDescriptor *colorAttachment = pRenderPassDesc->colorAttachments()->object(0);
        colorAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
        colorAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
        colorAttachment->setTexture(mtlDestTexture);

        MTL::RenderCommandEncoder *pEncoder = commandBuffer->renderCommandEncoder(pRenderPassDesc);

        // Set the pipeline that will be used for this render pass.
        pEncoder->setRenderPipelineState(m_pipeline);
        pEncoder->setVertexBuffer(m_vertexBuffer, 0, 0);
        pEncoder->setFragmentTexture(mtlTextureWrapper->Texture, 0);
        pEncoder->setFragmentSamplerState(mtlTextureWrapper->Sampler, 0);
        pEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 0, 6, 1);

        pEncoder->endEncoding();
        commandBuffer->commit();
    }
}

#endif // __APPLE__
