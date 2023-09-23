#include "util/wgpu/WebGPUFragmentStateUtil.hpp"

namespace bns
{
    WGPUFragmentState WebGPUFragmentStateUtil::Create(WGPUShaderModule fragmentShaderModule, WGPUColorTargetState colorTarget, std::string function)
    {
        WGPUFragmentState fragment = {};
        fragment.nextInChain = nullptr;
        fragment.module = fragmentShaderModule;
        fragment.entryPoint = function.c_str();
        fragment.targetCount = 1;
        fragment.targets = &colorTarget;

        return fragment;
    }
}