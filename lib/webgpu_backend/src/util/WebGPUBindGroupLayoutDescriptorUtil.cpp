#include "util/WebGPUBindGroupLayoutDescriptorUtil.hpp"

namespace bns
{
    WGPUBindGroupLayoutDescriptor WebGPUBindGroupLayoutDescriptorUtil::Create(
        WGPUBindGroupLayoutEntry *bindGroupLayoutEntries,
        u32 count)
    {
        WGPUBindGroupLayoutDescriptor bindGroupLayoutDescriptor = {};
        bindGroupLayoutDescriptor.nextInChain = nullptr;
        bindGroupLayoutDescriptor.entryCount = count;
        bindGroupLayoutDescriptor.entries = bindGroupLayoutEntries;

        return bindGroupLayoutDescriptor;
    }

    WGPUBindGroupLayoutDescriptor WebGPUBindGroupLayoutDescriptorUtil::Create(
        WGPUBindGroupLayoutEntry *bindGroupLayoutEntries,
        u32 count,
        std::string &label /* = "" */)
    {
        WGPUBindGroupLayoutDescriptor bindGroupDescriptor = Create(bindGroupLayoutEntries, count);
        bindGroupDescriptor.label = label.c_str();
        return bindGroupDescriptor;
    }

}