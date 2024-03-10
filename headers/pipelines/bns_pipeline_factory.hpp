#ifndef BNS_PIPELINE_FACTORY_HPP

#define BNS_PIPELINE_FACTORY_HPP

#include "renderer/bns_renderer.hpp"
#include "pipelines/bns_unlit_render_pipeline.hpp"
#include "buffers/bns_uniform_buffer.hpp"
#include "buffers/bns_instance_buffer.hpp"
#include "math/bns_mat4x4.hpp"

namespace bns
{
    /// @brief The pipeline factory.
    class PipelineFactory
    {
    private:
        Renderer *m_renderer;

    public:
        /// @brief Constructor.
        /// @param renderer The renderer.
        PipelineFactory(Renderer *renderer);

        /// @brief Create a unlit render pipeline.
        UnlitRenderPipeline *CreateUnlitRenderPipeline(UniformBuffer<Mat4x4f> *cameraBuffer, InstanceBuffer<Mat4x4f> *modelBuffer);
    };
} // namespace bns

#endif