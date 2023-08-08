#include "util/wgpu/WebGPUPipelineLayoutDescriptorUtil.hpp"

namespace bns
{
    WGPUPipelineLayoutDescriptor WebGPUPipelineLayoutDescriptorUtil::CreatePipelineLayoutDescriptor(WGPUBindGroupLayout *bindGroupLayout, u32 bindGroupLayoutCount)
    {
        WGPUPipelineLayoutDescriptor pipelineLayoutDescriptor;
        pipelineLayoutDescriptor.bindGroupLayouts = bindGroupLayout;
        pipelineLayoutDescriptor.bindGroupLayoutCount = bindGroupLayoutCount;
        pipelineLayoutDescriptor.label = nullptr;
        pipelineLayoutDescriptor.nextInChain = nullptr;

        return pipelineLayoutDescriptor;
    }
}