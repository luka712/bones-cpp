#if USE_METAL

#include "util/bns_metal_render_pipeline_state_util.hpp"
#include "bns_types.hpp"

namespace bns
{
    MTL::RenderPipelineState *MetalRenderPipelineStateUtil::Create(
        MTL::Device *device,
        MTL::Library *library,
        std::string vertexFunction,
        std::string fragmentFunction,
        std::string label)
    {
        // Setup ns strings
        NS::String *nsLabel = NS::String::string(label.c_str(), NS::StringEncoding::UTF8StringEncoding);
        NS::String *nsVertexFunction = NS::String::string(vertexFunction.c_str(), NS::StringEncoding::UTF8StringEncoding);
        NS::String *nsFragmentFunction = NS::String::string(fragmentFunction.c_str(), NS::StringEncoding::UTF8StringEncoding);

        // Setup library functions
        MTL::Function *vertexFn = library->newFunction(nsVertexFunction);
        MTL::Function *fragmentFn = library->newFunction(nsFragmentFunction);

        // Descriptor
        MTL::RenderPipelineDescriptor *descriptor = MTL::RenderPipelineDescriptor::alloc()->init();
        descriptor->setLabel(nsLabel);
        descriptor->setVertexFunction(vertexFn);
        descriptor->setFragmentFunction(fragmentFn);
        descriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

        // Pipeline
        NS::Error *error = nullptr;
        MTL::RenderPipelineState *pipeline = device->newRenderPipelineState(descriptor, &error);

        if (error != nullptr)
        {
            std::string errorString = error->localizedDescription()->utf8String();
            std::string msg = "MetalRenderPipelineStateUtil::Create: Failed to create render pipeline state. Error: " + errorString + ".";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        };

        // Release
        descriptor->release();

        vertexFn->release();
        fragmentFn->release();

        nsLabel->release();
        nsVertexFunction->release();
        nsFragmentFunction->release();

        return pipeline;
    }

    void MetalRenderPipelineStateUtil::Dispose(MTL::RenderPipelineState *pipeline)
    {
        pipeline->release();
    }
}

#endif
