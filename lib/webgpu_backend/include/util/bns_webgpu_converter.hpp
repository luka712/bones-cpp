#if USE_WEBGPU

#ifndef BNS_WEBGPU_CONVERTER_HPP

#define BNS_WEBGPU_CONVERTER_HPP

#include "bns_types.hpp"
#include "bns_webgpu.hpp"
#include "texture/bns_texture2d.hpp"

namespace bns
{
    struct WebGPUConverter 
    {
        /// @brief Convert the texture format to WebGPU texture format.
        static WGPUTextureFormat Convert(TextureFormat format);
    };
}

#endif 

#endif 