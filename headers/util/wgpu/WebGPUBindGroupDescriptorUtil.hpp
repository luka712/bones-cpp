#ifndef BNS_WEBGPU_BIND_GROUP_DESCRIPTOR_UTIL_HPP

#define BNS_WEBGPU_BIND_GROUP_DESCRIPTOR_UTIL_HPP

#include <webgpu/webgpu.h>
#include "data/Types.hpp"

namespace bns 
{
    struct WebGPUBindGroupDescriptorUtil final 
    {
        /**
         * @brief Create a bind group descriptor
         * @param layout - The bind group layout
         * @param entry - The bind group entry
         * @param entryCount - The bind group entry count
         * @return WGPUBindGroupDescriptor - The bind group descriptor
        */
        static WGPUBindGroupDescriptor Create(WGPUBindGroupLayout layout, WGPUBindGroupEntry* entry, u32 entryCount);
    };
}

#endif 