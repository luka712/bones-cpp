#if USE_OPENGLES

#ifndef BNS_OpenGLES_TEXTURE_2D_HPP

#define BNS_OpenGLES_TEXTURE_2D_HPP

#include "texture/Texture2D.hpp"
#include "ImageData.hpp"
#include "BnsOpenGLES.hpp"

namespace bns
{
    class OpenGLESTexture2D final : public Texture2D
    {
    private:
        /// @brief Temporary image data. To be released by user after texture is initialized.
        ImageData *m_imageData;

        /// @brief Convert the texture format to OpenGLES texture format.
        GLenum Convert(TextureFormat format) const;

    public:
        /// @brief The texture id which can be bound to the pipeline.
        GLuint Texture;

        /// @brief The constructor.
        OpenGLESTexture2D(ImageData *imageData, i32 textureUsageFlags, TextureFormat format);

        ~OpenGLESTexture2D();

        /// @brief Initialize the texture.
        void Initialize() override;

        /// @brief Release the texture.
        void Release() override;
    };
}

#endif // !BNS_OpenGLES_TEXTURE_2D_HPP

#endif // USE_OpenGLES