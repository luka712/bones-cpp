#include "util/wgpu/WebGPUBindGroupLayoutDescriptorUtil.hpp"

namespace bns
{
    WGPUBindGroupLayoutDescriptor WebGPUBindGroupLayoutDescriptorUtil::Create(WGPUBindGroupLayoutEntry *bindGroupLayoutEntries, u32 count)
    {
        WGPUBindGroupLayoutDescriptor bindGroupLayoutDescriptor = {};
        bindGroupLayoutDescriptor.nextInChain = nullptr;
        bindGroupLayoutDescriptor.entryCount = count;
        bindGroupLayoutDescriptor.entries = bindGroupLayoutEntries;

        return bindGroupLayoutDescriptor;
    }
}