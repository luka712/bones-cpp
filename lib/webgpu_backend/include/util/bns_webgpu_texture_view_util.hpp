#if USE_WEBGPU

#ifndef BNS_WEBGPU_TEXTURE_VIEW_UTIL_HPP

#define BNS_WEBGPU_TEXTURE_VIEW_UTIL_HPP

#include "bns_webgpu.hpp"
#include <string>
#include "texture/bns_texture2d.hpp"

namespace bns
{
    /// @brief The texture view utility.
    struct WebGPUTextureViewUtil
    {
        /// @brief Create a texture view.
        /// @param texture The texture.
        /// @param textureFormat The texture format.
        /// @param label The label.
        /// @return The texture view.
        static WGPUTextureView Create(WGPUTexture texture, TextureFormat textureFormat, std::string label = "");

        /// @brief Dispose the texture view.
        /// @param textureView The texture view.
        static void Dispose(WGPUTextureView textureView);
    };
}

#endif

#endif