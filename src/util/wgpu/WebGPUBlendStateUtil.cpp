#include "util/wgpu/WebGPUBlendStateUtil.hpp"

namespace bns
{
    void WebGPUBlendStateUtil::SetDefault(WGPUBlendState &blendState)
    {
        blendState.color.operation = WGPUBlendOperation_Add;
        blendState.color.srcFactor = WGPUBlendFactor_One;
        blendState.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
        blendState.alpha.operation = WGPUBlendOperation_Add;
        blendState.alpha.srcFactor = WGPUBlendFactor_One;
        blendState.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    }

    WGPUBlendState WebGPUBlendStateUtil::Create()
    {
        WGPUBlendState blendState = {};
        SetDefault(blendState);
        return blendState;
    }
}