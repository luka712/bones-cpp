#if USE_METAL

#ifndef BNS_METAL_UNLIT_RENDER_PIPELINE_HPP

#define BNS_METAL_UNLIT_RENDER_PIPELINE_HPP

#include "renderer/bns_renderer.hpp"
#include "bns_metal.hpp"
#include "pipelines/bns_unlit_render_pipeline.hpp"
#include "buffers/bns_metal_uniform_buffer.hpp"
#include "math/bns_mat4x4.hpp"
#include "buffers/bns_metal_vertex_buffer.hpp"
#include "buffers/bns_metal_index_buffer.hpp"

namespace bns
{
    class MetalRenderer;

    /// @brief The Metal unlit render pipeline class.
    class MetalUnlitRenderPipeline : public UnlitRenderPipeline
    {
    private:
        MetalRenderer *m_renderer;

        // Library
        MTL::Library *m_library;

        // The pipeline
        MTL::RenderPipelineState *m_pipeline;

        // Buffers
        MetalUniformBuffer<Mat4x4f> *m_cameraBuffer;
        MetalUniformBuffer<Mat4x4f> *m_modelBuffer;
        MetalUniformBuffer<Vec2f> *m_textureTillingBuffer;
        MetalUniformBuffer<Color> *m_diffuseColorBuffer;

        /// @brief Create the library. This is responsible for reading a shader.
        void CreateLibrary();

        /// @brief Create the pipeline. This is creating the rendering pipeline.
        void CreatePipeline();

        /// @brief Create the resources.
        void CreateResources();

    public:
        MetalUnlitRenderPipeline(Renderer *renderer, MetalUniformBuffer<Mat4x4f> *cameraBuffer, MetalUniformBuffer<Mat4x4f> *modelBuffer);

        void SetDiffuseColor(Color color) override;

        void SetTextureTilling(Vec2f tilling) override;

        void SetDiffuseTexture(Texture2D *texture) override;

        void Initialize() override;

        /// @brief Render the pipeline.
        /// @param vertexBuffer The vertex buffer.
        /// @param indexBuffer The index buffer.
        /// @param instanceCount The instance count. By default it is 1.
        void Render(MetalVertexBuffer &vertexBuffer, MetalIndexBuffer &indexBuffer, u32 instanceCount = 1);

        void Dispose();
    };
} // namespace bns

#endif

#endif // USE_METAL
