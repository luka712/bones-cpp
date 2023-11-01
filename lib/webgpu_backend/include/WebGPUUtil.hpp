#ifndef BNS_WEBGPU_UTIL

#define BNS_WEBGPU_UTIL

#include "util/WebGPUTextureViewDescriptorUtil.hpp"



namespace bns
{
    /// @brief The WebGPU util, holds all the utility classes that cab help with 
    /// allocating and creating WebGPU resources.
    struct WebGPUUtil final
    {
        /// @brief The texture view descriptor util.
        static WebGPUTextureViewDescriptorUtil TextureViewDescriptor;
       
    };
}

#endif