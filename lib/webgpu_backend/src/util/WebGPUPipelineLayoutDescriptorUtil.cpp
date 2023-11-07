#include "util/WebGPUPipelineLayoutDescriptorUtil.hpp"

namespace bns
{
    WGPUPipelineLayoutDescriptor WebGPUPipelineLayoutDescriptorUtil::Create(WGPUBindGroupLayout *bindGroupLayout, size_t bindGroupLayoutCount)
    {
        WGPUPipelineLayoutDescriptor pipelineLayoutDescriptor;
        pipelineLayoutDescriptor.bindGroupLayouts = bindGroupLayout;
        pipelineLayoutDescriptor.bindGroupLayoutCount = bindGroupLayoutCount;
        pipelineLayoutDescriptor.label = nullptr;
        pipelineLayoutDescriptor.nextInChain = nullptr;

        return pipelineLayoutDescriptor;
    }
}
