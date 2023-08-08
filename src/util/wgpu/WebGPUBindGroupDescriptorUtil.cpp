#include "util/wgpu/WebGPUBindGroupDescriptorUtil.hpp"

namespace bns 
{
    WGPUBindGroupDescriptor WebGPUBindGroupDescriptorUtil::Create(WGPUBindGroupLayout layout, WGPUBindGroupEntry* entry, u32 entryCount)
    {
        WGPUBindGroupDescriptor bindGroupDescriptor = {};
        bindGroupDescriptor.layout = layout;
        bindGroupDescriptor.entryCount = entryCount;
        bindGroupDescriptor.entries = entry;
        return bindGroupDescriptor;
    }
}