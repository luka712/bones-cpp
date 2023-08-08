#ifndef BNS_WEBGPU_FRAGMENT_STATE_UTIL_HPP

#define BNS_WEBGPU_FRAGMENT_STATE_UTIL_HPP

#include <webgpu/webgpu.h>
#include <string>
#include "data/Types.hpp"

namespace bns 
{
    struct WebGPUFragmentStateUtil final 
    {
        /**
         * @brief Create a fragment state
         * @param fragmentShaderModule The fragment shader module
         * @param colorTargetState The color target state
         * @param function The function name
         * @return The fragment state
        */
        static WGPUFragmentState Create(WGPUShaderModule fragmentShaderModule, WGPUColorTargetState colorTarget, std::string function);

    };
}

#endif 