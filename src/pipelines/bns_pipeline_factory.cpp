#include "pipelines/bns_pipeline_factory.hpp"

#if USE_METAL
#include "pipelines/bns_metal_unlit_render_pipeline.hpp"
#endif

namespace bns
{
    PipelineFactory::PipelineFactory(Renderer *renderer)
    {
        m_renderer = renderer;
    }

    UnlitRenderPipeline *PipelineFactory::CreateUnlitRenderPipeline(UniformBuffer<Mat4x4f> *cameraBuffer, InstanceBuffer<Mat4x4f> *modelBuffer)
    {

        UnlitRenderPipeline* pipeline = nullptr;

#if USE_METAL
        if(m_renderer->GetRendererType() == RendererType::Metal)
        {
            pipeline = new MetalUnlitRenderPipeline(
                static_cast<MetalRenderer*>(m_renderer),
                static_cast<MetalUniformBuffer<Mat4x4f> *>(cameraBuffer),
                static_cast<MetalInstanceBuffer<Mat4x4f> *>(modelBuffer));
        }
#endif

        pipeline->Initialize();

        return pipeline;
    }
}