#if USE_OPENGL

#ifndef BNS_OPENGL_TEXTURE_UTIL_HPP

#define BNS_OPENGL_TEXTURE_UTIL_HPP

#include "bns_opengl.hpp"
#include "bns_types.hpp"
#include "bns_rendering_backend_types.hpp"
#include <string>

namespace bns
{
    /// @brief The OpenGL texture utility.
    struct OpenGLTextureUtil
    {
        /// @brief Create a 2D texture.
        /// @param width The width of the texture.
        /// @param height The height of the texture.
        /// @param data The data of the texture.
        /// @param label The label of the texture. By default is "".
        /// @param format The format of the texture. By default is BGRA_8_Unorm.
        /// @param minFilter The min filter of the texture. By default is LINEAR.
        /// @param magFilter The mag filter of the texture. By default is LINEAR.
        /// @return
        static GLuint CreateTexture2D(
            u32 width, u32 height,
            void *data,
            std::string label = "",
            TextureFormat format = TextureFormat::BGRA_8_Unorm,
            SamplerMinFilter minFilter = SamplerMinFilter::LINEAR,
            SamplerMagFilter magFilter = SamplerMagFilter::LINEAR);
    };
} // namespace bns

#endif

#endif // USE_OPENGL