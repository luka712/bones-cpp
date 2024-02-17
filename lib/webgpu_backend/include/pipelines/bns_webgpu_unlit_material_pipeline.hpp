#if USE_WEBGPU

#ifndef BNS_UNLIT_MATERIAL_PIPELINE

#define BNS_UNLIT_MATERIAL_PIPELINE

#include "renderer/bns_renderer.hpp"
#include "bns_webgpu.hpp"

namespace bns 
{
    class WebGPUUnlitMaterialPipeline
    {
        private:
            WGPUDevice m_device;

            // Bind group layouts
            WGPUBindGroupLayout m_modelBindGroupLayout;
            WGPUBindGroupLayout m_cameraBindGroupLayout;
            WGPUBindGroupLayout m_textureBindGroupLayout;
            WGPUBindGroupLayout m_materialBindGroupLayout;

            void CreateBindGroupLayouts();

        public:
            /// @brief The constructor.
            /// @param renderer The renderer.
            WebGPUUnlitMaterialPipeline(Renderer* renderer);

            /// @brief Initialize the pipeline.
            void Initialize();

            /// @brief Dispose of pipeline.
            void Dispose();
    };
}

#endif 

#endif 