
#if USE_METAL

#include "sprite/MetalUnlitSpritePipeline.hpp"
#include "FileLoader.hpp"
#include "MetalUtil.hpp"

namespace bns
{
    MetalUnlitSpritePipeline::MetalUnlitSpritePipeline(MTL::RenderPipelineState *pipeline,
                                             MetalTexture2D *texture)
        : m_pipeline(pipeline), m_texture(texture)
    {
        InstanceIndex = 0;
    }

    // NOTE: STATIC FUNCTION
    MetalUnlitSpritePipeline *MetalUnlitSpritePipeline::Create(
        MetalRenderer& renderer,
        MetalTexture2D *texture)
    {
        MTL::Device *device = renderer.GetDevice();

        FileLoader fileLoader;
        std::string shaderSource = fileLoader.LoadFile("shaders/metal/sprite/unlit_sprite.metal");
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
        MetalUtil::RenderPipelineColorAttachmentDescriptor.SetDefault(*colorAttachment);

        // set 2nd color attachment, for bloom/brightness
        if (renderer.GetBrightnessTexture() != nullptr)
        {
            MTL::RenderPipelineColorAttachmentDescriptor *colorAttachment2 = pDesc->colorAttachments()->object(NS::UInteger(1));
            MetalUtil::RenderPipelineColorAttachmentDescriptor.SetDefault(*colorAttachment2);
        }
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

        return new MetalUnlitSpritePipeline(pipeline, texture);
    }
}

#endif // __APPLE__
