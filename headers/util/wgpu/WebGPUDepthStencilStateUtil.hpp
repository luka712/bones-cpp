#ifndef BNS_WEBGPU_DEPTH_STENCIL_STATE_HPP

#define BNS_WEBGPU_DEPTH_STENCIL_STATE_HPP

#include <webgpu/webgpu.h>

namespace bns 
{
    struct WebGPUDepthStencilStateUtil
    {
        static WGPUDepthStencilState Create();
    };
}

#endif 