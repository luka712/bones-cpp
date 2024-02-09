#ifndef BNS_WEBGPU_FRAGMENT_STATE_UTIL_HPP

#define BNS_WEBGPU_FRAGMENT_STATE_UTIL_HPP

#include <webgpu/webgpu.h>
#include <string>
#include "bns_types.hpp"

namespace bns 
{
    struct WebGPUFragmentStateUtil final 
    {
        
        /// @brief Create a fragment state
        /// @param fragmentShaderModule The fragment shader module
        /// @param colorTargetState The color target state
        /// @param function The function name.
        /// @return The fragment state
        /// @note The function name is the name of the fragment shader main function.
        /// It must not be delted until the fragment state is used to create a render pipeline.
        static WGPUFragmentState Create(WGPUShaderModule& fragmentShaderModule, WGPUColorTargetState& colorTargetState, std::string& function);

        /// @brief Create a fragment state
        /// @param fragmentShaderModule The fragment shader module
        /// @param colorTargetState Point to color target state or collection of color target states.
        /// @param colorTargetCount The number of color target states.
        /// @param function The function name.
        /// @return The fragment state
        /// @note The function name is the name of the fragment shader main function.
        /// It must not be delted until the fragment state is used to create a render pipeline.
        static WGPUFragmentState Create(WGPUShaderModule& fragmentShaderModule, WGPUColorTargetState *colorTargetState, i32 colorTargetCount, std::string& function);

    };
}

#endif 
