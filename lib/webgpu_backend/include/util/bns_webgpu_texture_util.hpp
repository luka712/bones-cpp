#if USE_WEBGPU

#ifndef BNS_WEBGPU_TEXTURE_UTIL_HPP

#define BNS_WEBGPU_TEXTURE_UTIL_HPP

#include "bns_webgpu.hpp"
#include "bns_types.hpp"
#include "bns_rendering_backend_types.hpp"

namespace bns
{
    struct WebGPUTextureUtil
    {
        /// @brief Create an empty texture.
        /// @param device The device.
        /// @param width The width.
        /// @param height The height.
        /// @param format The format.
        /// @param textureUsage The texture usage.
        /// @return The texture.
        static WGPUTexture Create(WGPUDevice device, u32 width, u32 height, TextureFormat format, TextureUsage textureUsage);

        /// @brief Create a readonly texture from an image. 
        /// @param device The device.
        /// @param queue The queue.
        /// @param width The width.
        /// @param height The height.
        /// @param format The format.
        /// @param textureUsage The texture usage.
        /// @param data The data.
        /// @return The texture.
        static WGPUTexture Create(WGPUDevice device, WGPUQueue queue, u32 width, u32 height, TextureFormat format, TextureUsage textureUsage, void *data);
    };
}

#endif

#endif