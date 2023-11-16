#ifdef USE_OPENGLES

#include "texture/OpenGLESTexture2D.hpp"
#include <exception>
namespace bns
{
    OpenGLESTexture2D::OpenGLESTexture2D(ImageData *imageData, i32 textureUsageFlags, TextureFormat format)
        : Texture2D(imageData->Width, imageData->Height, textureUsageFlags, format), m_imageData(imageData)
    {
    }

    OpenGLESTexture2D::~OpenGLESTexture2D()
    {
    }

    void OpenGLESTexture2D::Initialize()
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

    void OpenGLESTexture2D::Release()
    {
        glDeleteTextures(1, &Texture);
    }

    GLenum OpenGLESTexture2D::Convert(TextureFormat format) const
    {
        switch (format)
        {
        case TextureFormat::RGBA_8_Unorm:
            return GL_RGBA;
        default:
            throw std::exception("OpenGLESTexture2D::Convert: Unknown texture format.");
        }
    }
}

#endif