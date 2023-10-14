#include "sprite/metal/MetalSpritePipeline.hpp"
#include "loaders/FileLoader.hpp"
#include "util/MetalUtil.hpp"

namespace bns
{

    MetalSpritePipeline::MetalSpritePipeline(MTL::RenderPipelineState *pipeline,
                                             MetalTexture2D *texture)
        : m_pipeline(pipeline), m_texture(texture) {
            InstanceIndex = 0;
        }

    // NOTE: STATIC FUNCTION
    MetalSpritePipeline *MetalSpritePipeline::Create(MTL::Device *device, MetalTexture2D *texture, MTL::Buffer *projectionViewBuffer)
    {
        FileLoader fileLoader;
        std::string shaderSource = fileLoader.LoadFile("shaders/metal/sprite/sprite.metal");
        MTL::Library *pLibrary = MetalUtil::Library.Create(device, shaderSource);

        MTL::Function *pVertexFn = pLibrary->newFunction(NS::String::string("vs_main", NS::StringEncoding::UTF8StringEncoding));
        MTL::Function *pFragFn = pLibrary->newFunction(NS::String::string("fs_main", NS::StringEncoding::UTF8StringEncoding));

        MTL::RenderPipelineDescriptor *pDesc = MetalUtil::RenderPipelineDescriptor.Create(pVertexFn, pFragFn);

        // BUFFERS
        BufferLayoutDescriptor bufferLayoutDescriptor;
        bufferLayoutDescriptor.Step = StepMode::Vertex;
        bufferLayoutDescriptor.Stride = sizeof(f32) * FLOATS_PER_VERTEX;
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x4, 2, sizeof(f32) * 5});

        std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
        vertexBufferLayouts.push_back(bufferLayoutDescriptor);

        auto layoutsAttributesDto = MetalUtil::VertexBufferLayout.Create(vertexBufferLayouts);

        // vertex
        MTL::VertexDescriptor *pVertexDesc = pDesc->vertexDescriptor();

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
        MTL::RenderPipelineColorAttachmentDescriptor *colorAttachment = pDesc->colorAttachments()->object(NS::UInteger(0));
        colorAttachment->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);

        colorAttachment->setBlendingEnabled(true);

        colorAttachment->setRgbBlendOperation(MTL::BlendOperationAdd);
        colorAttachment->setSourceRGBBlendFactor(MTL::BlendFactorSourceAlpha);
        colorAttachment->setDestinationRGBBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);

        colorAttachment->setAlphaBlendOperation(MTL::BlendOperationAdd);
        colorAttachment->setSourceAlphaBlendFactor(MTL::BlendFactorSourceAlpha);
        colorAttachment->setDestinationAlphaBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);

        NS::Error *pError = nullptr;
        MTL::RenderPipelineState *pipeline = device->newRenderPipelineState(pDesc, &pError);
        if (!pipeline)
        {
            printf("%s", pError->localizedDescription()->utf8String());
            return nullptr;
        }

        pDesc->release();
        pFragFn->release();
        pVertexFn->release();
        pLibrary->release();

        return new MetalSpritePipeline(pipeline, texture);
    }
}
