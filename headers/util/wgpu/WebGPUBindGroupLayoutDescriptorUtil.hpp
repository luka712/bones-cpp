#ifndef BNS_WEBGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_UTIL_HPP

#define BNS_WEBGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_UTIL_HPP

#include <webgpu/webgpu.h>
#include <vector>
#include "data/Types.hpp"

namespace bns
{
    struct WebGPUBindGroupLayoutDescriptorUtil final
    {
        /**
         * @brief Create a bind group layout descriptor
         * @param bindGroupLayoutEntries The bind group layout entries
         * @return The bind group layout descriptor
         */
        static WGPUBindGroupLayoutDescriptor Create(WGPUBindGroupLayoutEntry *bindGroupLayoutEntries, u32 count);
    };
}

#endif