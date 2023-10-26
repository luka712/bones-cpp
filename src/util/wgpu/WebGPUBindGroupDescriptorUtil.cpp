#include "util/wgpu/WebGPUBindGroupDescriptorUtil.hpp"

namespace bns
{
    WGPUBindGroupDescriptor WebGPUBindGroupDescriptorUtil::Create(
        WGPUBindGroupLayout layout,
        WGPUBindGroupEntry *entry,
        u32 entryCount,
        std::string& label /* = "" */)
    {
        WGPUBindGroupDescriptor bindGroupDescriptor = Create(layout, entry, entryCount);
        bindGroupDescriptor.label = label.c_str();
        return bindGroupDescriptor;
    }


    WGPUBindGroupDescriptor WebGPUBindGroupDescriptorUtil::Create(
        WGPUBindGroupLayout layout,
        WGPUBindGroupEntry *entry,
        u32 entryCount)
    {
        WGPUBindGroupDescriptor bindGroupDescriptor = {};
        bindGroupDescriptor.layout = layout;
        bindGroupDescriptor.entryCount = entryCount;
        bindGroupDescriptor.entries = entry;
        return bindGroupDescriptor;
    }
}
