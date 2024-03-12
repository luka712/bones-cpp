#if USE_WEBGPU

#ifndef BNS_WEBGPU_CONVERTER_HPP

#define BNS_WEBGPU_CONVERTER_HPP

#include "bns_types.hpp"
#include "bns_webgpu.hpp"
#include "bns_rendering_backend_types.hpp"

namespace bns
{
    struct WebGPUConverter 
    {
        /// @brief Convert the texture format to WebGPU texture format.
        /// @param format The texture format.
        /// @return The WebGPU texture format.
        static WGPUTextureFormat Convert(TextureFormat format);

        /// @brief Convert the texture usage to WebGPU texture usage.
        /// @param textureUsage The texture usage.
        /// @return The WebGPU texture usage.
        static WGPUTextureUsage Convert(TextureUsage textureUsage);
    };
}

#endif 

#endif 