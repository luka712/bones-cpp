#ifndef BNS_WEBGPU_PIPELINE_LAYOUT_DESCRIPTOR_UTIL_HPP

#define BNS_WEBGPU_PIPELINE_LAYOUT_DESCRIPTOR_UTIL_HPP

#include <webgpu/webgpu.h>
#include "data/Types.hpp"

namespace bns 
{
    struct WebGPUPipelineLayoutDescriptorUtil final 
    {
        /**
         * @brief Create a Pipeline Layout Descriptor object
         * @param bindGroupLayout - The pointer to the bind group layout array start 
         * @param bindGroupLayoutCount - The number of bind group layouts
         * @return WGPUPipelineLayoutDescriptor - The pipeline layout descriptor
         * @note The bind group layout array must be valid until the pipeline layout is created.
        */
        static WGPUPipelineLayoutDescriptor Create(WGPUBindGroupLayout *bindGroupLayout, size_t bindGroupLayoutCount);
    };
}

#endif 