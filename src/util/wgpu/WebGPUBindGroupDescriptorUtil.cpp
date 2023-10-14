#include "util/wgpu/WebGPUBindGroupDescriptorUtil.hpp"

namespace bns 
{
    WGPUBindGroupDescriptor WebGPUBindGroupDescriptorUtil::Create(WGPUBindGroupLayout layout, WGPUBindGroupEntry* entry, u32 entryCount, std::string label)
    {
        WGPUBindGroupDescriptor bindGroupDescriptor = {};
        bindGroupDescriptor.label = label.c_str();
        bindGroupDescriptor.layout = layout;
        bindGroupDescriptor.entryCount = entryCount;
        bindGroupDescriptor.entries = entry;
        return bindGroupDescriptor;
    }
}