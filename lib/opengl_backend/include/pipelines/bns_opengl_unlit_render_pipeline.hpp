#if USE_OPENGL

#ifndef BNS_OPENGL_UNLIT_RENDER_PIPELINE_HPP

#define BNS_OPENGL_UNLIT_RENDER_PIPELINE_HPP

#include "pipelines/bns_unlit_render_pipeline.hpp"
#include "bns_opengl.hpp"
#include "math/bns_mat4x4.hpp"
#include "buffers/bns_opengl_instance_buffer.hpp"
#include "buffers/bns_opengl_uniform_buffer.hpp"
#include "buffers/bns_opengl_vertex_buffer.hpp"

namespace bns
{
    class OpenGLUnlitRenderPipeline : public UnlitRenderPipeline
    {
    private:
        u32 m_program;
        u32 m_vao;

        // Buffers
        OpenGLInstanceBuffer<Mat4x4f> *m_modelBuffer;
        OpenGLUniformBuffer<Mat4x4f> *m_cameraBuffer;
        OpenGLUniformBuffer<Vec2f> *m_textureTillingBuffer;
        OpenGLUniformBuffer<Color> *m_diffuseColorBuffer;

        // Cache.
        // Empty texture
        Texture2D *m_defaultEmptyTexture;
        GLuint m_lastVerticesBuffer;



        /// @brief Read shaders from file and create program.
        void CreateProgram();

        /// @brief Create VAO bindings. Takes care of creating a VAO and binding the vertex buffer and models instance buffer.
        /// @param vertexBuffer The vertex buffer.
        void CreateVAO(OpenGLVertexBuffer* vertexBuffer);

        /// @brief Create resources.
        void CreateResources();

    public:
        /// @brief The constructor.
        /// @param cameraBuffer The camera buffer.
        /// @param modelBuffer The model buffer.
        OpenGLUnlitRenderPipeline(UniformBuffer<Mat4x4f> *cameraBuffer, InstanceBuffer<Mat4x4f> *modelBuffer);

        /// @brief Set the diffuse texture.
        void SetDiffuseColor(Color color) override;

        /// @brief Set the texture tilling.
         void SetTextureTilling(Vec2f tilling) override;

        /// @brief Set the diffuse texture.
        void SetDiffuseTexture(Texture2D *texture) override;

        void Initialize() override;
        void Render(VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer, u32 instanceCount = 1) override;
        
        /// @brief Dispose of the resources.
        inline void Dispose() override
        {
            glDeleteProgram(m_program);
            glDeleteVertexArrays(1, &m_vao);
            m_textureTillingBuffer->Dispose();
            m_diffuseColorBuffer->Dispose();
        }
    };
} // namespace bns

#endif

#endif