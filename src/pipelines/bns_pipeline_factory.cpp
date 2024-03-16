#include "pipelines/bns_pipeline_factory.hpp"

#if USE_METAL
#include "pipelines/bns_metal_unlit_render_pipeline.hpp"
#endif

#if USE_WEBGPU
#include "pipelines/bns_webgpu_unlit_render_pipeline.hpp"
#endif

#if USE_OPENGL
#include "pipelines/bns_opengl_unlit_render_pipeline.hpp"
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

#if USE_WEBGPU
        if(m_renderer->GetRendererType() == RendererType::WebGPU)
        {
            pipeline = new WebGPUUnlitRenderPipeline(
                static_cast<WebGPURenderer*>(m_renderer),
                static_cast<WebGPUUniformBuffer<Mat4x4f> *>(cameraBuffer),
                static_cast<WebGPUInstanceBuffer<Mat4x4f> *>(modelBuffer));
        }
#endif

#if USE_OPENGL
        if(m_renderer->GetRendererType() == RendererType::OpenGL)
        {
            pipeline = new OpenGLUnlitRenderPipeline(
                static_cast<OpenGLUniformBuffer<Mat4x4f> *>(cameraBuffer),
                static_cast<OpenGLInstanceBuffer<Mat4x4f> *>(modelBuffer));
        }
#endif
        pipeline->Initialize();

        return pipeline;
    }
}