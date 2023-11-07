#include "util/WebGPUFragmentStateUtil.hpp"

namespace bns
{
    WGPUFragmentState WebGPUFragmentStateUtil::Create(
        WGPUShaderModule &fragmentShaderModule,
        WGPUColorTargetState &colorTarget,
        std::string &function)
    {
        return Create(fragmentShaderModule, &colorTarget, 1, function);
    }

     WGPUFragmentState WebGPUFragmentStateUtil::Create(
        WGPUShaderModule &fragmentShaderModule,
        WGPUColorTargetState *colorTargetState,
        i32 colorTargetCount,
        std::string &function)
    {
        WGPUFragmentState fragment = {};
        fragment.nextInChain = nullptr;
        fragment.module = fragmentShaderModule;
        fragment.entryPoint = function.c_str();
        fragment.targetCount = colorTargetCount;
        fragment.targets = colorTargetState;

        return fragment;
    }
}
