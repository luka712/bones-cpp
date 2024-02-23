#if USE_WEBGPU

#ifndef BNS_WEBGPU_PIPELINE_LAYOUT_UTIL

#define BNS_WEBGPU_PIPELINE_LAYOUT_UTIL

#include "bns_webgpu.hpp"
#include <vector>

namespace bns
{
    struct WebGPUPipelineLayoutUtil
    {
        /// @brief Create a new pipeline layout.
        /// @param device The device.
        /// @param bindGroupLayouts The bind group layouts.
        /// @return The pipeline layout.
        static WGPUPipelineLayout Create(WGPUDevice device, std::vector<WGPUBindGroupLayout> bindGroupLayouts);

        /// @brief Dispose of a pipeline layout.
        /// @param pipelineLayout The pipeline layout.
        static void Dispose(WGPUPipelineLayout pipelineLayout);
    };
}

#endif

#endif