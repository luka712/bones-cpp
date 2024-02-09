#if USE_OPENGL

#ifndef BNS_OPENGL_TEXTURE_2D_HPP

#define BNS_OPENGL_TEXTURE_2D_HPP

#include "texture/Texture2D.hpp"
#include "ImageData.hpp"
#include "BnsOpenGL.hpp"

namespace bns
{
    class OpenGLTexture2D final : public Texture2D
    {
    private:
        /// @brief Temporary image data. To be released by user after texture is initialized.
        ImageData *m_imageData;

        /// @brief Convert the texture format to OpenGL texture format.
        GLenum Convert(TextureFormat format) const;

        /// @brief Convert the sampler min filter to OpenGL flag.
        /// @param samplerMinFilter The min filter.
        /// @return The correct OpenGL flag.
        GLenum Convert(SamplerMinFilter samplerMinFilter);

        /// @brief Convert the sampler mag filter to OpenGL flag.
        /// @param samplerMinFilter The mag filter.
        /// @return The correct OpenGL flag.
        GLenum Convert(SamplerMagFilter samplerMagFilter);

    public:
        /// @brief The texture id which can be bound to the pipeline.
        GLuint Texture;

        /// @brief The constructor.
        /// @param imageData The image data.
        /// @param textureUsageFlags The texture usage flags.
        /// @param format The texture format.
        /// @param samplerMinFilter The sampler min filter.
        /// @param samplerMagFilter The sampler mag filter.
        OpenGLTexture2D(ImageData *imageData, 
             i32 textureUsageFlags,
             TextureFormat format,
             SamplerMinFilter samplerMinFilter,
             SamplerMagFilter samplerMagFilter);

        ~OpenGLTexture2D();

        /// @brief Initialize the texture.
        void Initialize() override;

        /// @brief Release the texture.
        void Release() override;
    };
}

#endif // !BNS_OPENGL_TEXTURE_2D_HPP

#endif // USE_OPENGL