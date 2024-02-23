#if USE_WEBGPU

#ifndef BNS_UNLIT_MATERIAL_PIPELINE

#define BNS_UNLIT_MATERIAL_PIPELINE

#include "renderer/bns_renderer.hpp"
#include "constant_buffer/bns_webgpu_constant_buffer.hpp"
#include "math/bns_mat4x4.hpp"
#include "renderer/bns_webgpu_renderer.hpp"

namespace bns 
{
    class WebGPUUnlitMaterialPipeline
    {
        private:
            WebGPURenderer* m_renderer;
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
            WebGPUConstantBuffer<Mat4x4f>* m_cameraBuffer;
            WebGPUConstantBuffer<Mat4x4f>* m_modelBuffer;
            WebGPUConstantBuffer<Mat4x4f>* m_textureTillingBuffer;
            WebGPUConstantBuffer<Mat4x4f>* m_diffuseColorBuffer;

            /// @brief Create the shader module.
            void CreateShaderModule();

            /// @brief Create the bind group layouts.
            void CreateBindGroupLayouts();

            /// @brief Create the pipeline layout.
            void CreatePipelineLayout();

            /// @brief Create the buffers.
            void CreateBuffers();

            /// @brief Create the pipeline.
            void CreatePipeline();

        public:
            /// @brief The constructor.
            /// @param renderer The renderer.
            /// @param cameraBuffer The camera buffer.
            /// @param modelBuffer The model buffer.
            WebGPUUnlitMaterialPipeline(Renderer* renderer, ConstantBuffer<Mat4x4f>* cameraBuffer, ConstantBuffer<Mat4x4f>* modelBuffer);

            /// @brief Initialize the pipeline.
            void Initialize();

            /// @brief Dispose of pipeline.
            void Dispose();
    };
}

#endif 

#endif 