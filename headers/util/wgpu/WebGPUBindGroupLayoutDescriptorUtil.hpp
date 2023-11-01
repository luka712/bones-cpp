#ifndef BNS_WEBGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_UTIL_HPP

#define BNS_WEBGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_UTIL_HPP

#include <webgpu/webgpu.h>
#include <vector>
#include "Types.hpp"
#include <string>

namespace bns
{
    struct WebGPUBindGroupLayoutDescriptorUtil final
    {
        /**
         * @brief Create a bind group layout descriptor
         * @param bindGroupLayoutEntries The bind group layout entries
         * @param count The count of the bind group layout entries
         * @param label The label. Default is empty string
         * @return The bind group layout descriptor
         */
        static WGPUBindGroupLayoutDescriptor Create(WGPUBindGroupLayoutEntry *bindGroupLayoutEntries, u32 count, std::string &label);

        /**
         * @brief Create a bind group layout descriptor
         * @param bindGroupLayoutEntries The bind group layout entries
         * @param count The count of the bind group layout entries
         * @return The bind group layout descriptor
         */
        static WGPUBindGroupLayoutDescriptor Create(WGPUBindGroupLayoutEntry *bindGroupLayoutEntries, u32 count);
    };
}

#endif