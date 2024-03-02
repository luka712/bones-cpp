#if USE_WEBGPU

#ifndef BNS_UNLIT_MATERIAL_PIPELINE

#define BNS_UNLIT_MATERIAL_PIPELINE

#include "renderer/bns_renderer.hpp"
#include "buffers/bns_webgpu_uniform_buffer.hpp"
#include "buffers/bns_webgpu_vertex_buffer.hpp"
#include "buffers/bns_webgpu_index_buffer.hpp"
#include "math/bns_mat4x4.hpp"
#include "renderer/bns_webgpu_renderer.hpp"
#include "texture/bns_webgpu_texture2d.hpp"


namespace bns
{
    class WebGPUUnlitMaterialPipeline
    {
    private:
        WebGPURenderer *m_renderer;
        WGPUDevice m_device;

        // Pipeline
        WGPURenderPipeline m_pipeline;

        // Shader module
        WGPUShaderModule m_shaderModule;

        // Bind group layouts
        WGPUBindGroupLayout m_modelBindGroupLayout;
        WGPUBindGroupLayout m_cameraBindGroupLayout;
        WGPUBindGroupLayout m_textureBindGroupLayout;
        WGPUBindGroupLayout m_materialBindGroupLayout;

        // Pipeline layout
        WGPUPipelineLayout m_pipelineLayout;

        // Buffers
        WebGPUUniformBuffer<Mat4x4f> *m_cameraBuffer;
        WebGPUUniformBuffer<Mat4x4f> *m_modelBuffer;
        WebGPUUniformBuffer<Vec2f> *m_textureTillingBuffer;
        WebGPUUniformBuffer<Color> *m_diffuseColorBuffer;

        // Bind groups
        WGPUBindGroup m_modelBindGroup;
        WGPUBindGroup m_cameraBindGroup;
        WGPUBindGroup m_textureBindGroup;
        WGPUBindGroup m_materialBindGroup;

        WebGPUTexture2D *m_diffuseTexture;
        Color m_diffuseColor;
        Vec2f m_textureTilling;

        /// @brief Create the shader module.
        void CreateShaderModule();

        /// @brief Create the bind group layouts.
        void CreateBindGroupLayouts();

        /// @brief Create the pipeline layout.
        void CreatePipelineLayout();

        /// @brief Create the resources.
        void CreateResources();

        /// @brief Create the pipeline.
        void CreatePipeline();

        /// @brief Create the bind groups.
        void CreateBindGroups();

        /// @brief Create diffuse texture bind group.
        void CreateDiffuseTextureBindGroup();

    public:
        /// @brief The constructor.
        /// @param renderer The renderer.
        /// @param cameraBuffer The camera buffer.
        /// @param modelBuffer The model buffer.
        WebGPUUnlitMaterialPipeline(Renderer *renderer, UniformBuffer<Mat4x4f> *cameraBuffer, UniformBuffer<Mat4x4f> *modelBuffer);

        /// @brief Set the diffuse texture.
        inline Color GetDiffuseColor() const { return m_diffuseColor; }

        /// @brief Set the diffuse texture.
        void SetDiffuseColor(Color color);

        /// @brief Get the texture tilling.
        inline Vec2f GetTextureTilling() const { return m_textureTilling; }

        /// @brief Set the texture tilling.
        void SetTextureTilling(Vec2f tilling);

        /// @brief Get the diffuse texture.
        inline WebGPUTexture2D *GetDiffuseTexture() const { return m_diffuseTexture; }

        /// @brief Set the diffuse texture.
        void SetDiffuseTexture(WebGPUTexture2D *texture);

        /// @brief Initialize the pipeline.
        void Initialize();

        /// @brief Render the pipeline.
        /// @param vertexBuffer The vertex buffer.
        /// @param indexBuffer The index buffer.
        /// @param instanceCount The number of instances to render. By default, it is 1.
        void Render(WebGPUVertexBuffer& vertexBuffer, WebGPUIndexBuffer& indexBuffer, u32 instanceCount = 1);

        /// @brief Dispose of pipeline.
        void Dispose();
    };
}

#endif

#endif