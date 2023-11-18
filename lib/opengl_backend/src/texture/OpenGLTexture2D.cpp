#if USE_OPENGL

#include <stdexcept>
#include "texture/OpenGLTexture2D.hpp"


namespace bns
{
    OpenGLTexture2D::OpenGLTexture2D(ImageData *imageData, i32 textureUsageFlags, TextureFormat format)
        : Texture2D(imageData->Width, imageData->Height, textureUsageFlags, format), m_imageData(imageData)
    {
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
    }

    void OpenGLTexture2D::Initialize()
    {
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);

        GLenum format = Convert(m_format);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_imageData->Width, m_imageData->Height, 0, format, GL_UNSIGNED_BYTE, m_imageData->Data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture2D::Release()
    {
        glDeleteTextures(1, &Texture);
    }

    GLenum OpenGLTexture2D::Convert(TextureFormat format) const
    {
        switch (format)
        {
        case TextureFormat::RGBA_8_Unorm:
            return GL_RGBA;
        case TextureFormat::BGRA_8_Unorm:
            return GL_BGRA;
        default:
            throw std::runtime_error("OpenGLTexture2D::Convert: Unknown texture format.");
        }
    }
}

#endif
