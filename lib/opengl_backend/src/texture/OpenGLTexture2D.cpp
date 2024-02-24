#if USE_OPENGL

#include <stdexcept>
#include "texture/OpenGLTexture2D.hpp"

namespace bns
{
    OpenGLTexture2D::OpenGLTexture2D(ImageData *imageData, i32 textureUsageFlags, TextureFormat format, SamplerMinFilter samplerMinFilter,
                                     SamplerMagFilter samplerMagFilter)
        : Texture2D(imageData->Width, imageData->Height, textureUsageFlags, format, samplerMinFilter, samplerMagFilter), m_imageData(imageData)
    {
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
    }

    GLenum OpenGLTexture2D::Convert(SamplerMinFilter samplerMinFilter)
    {
        if(samplerMinFilter == SamplerMinFilter::LINEAR)
        {
            return GL_LINEAR;
        }
        else if(samplerMinFilter == SamplerMinFilter::NEAREST)
        {
            return GL_NEAREST;
        }

        std::string msg = "OpenGLTexture2D::Convert: Unable to convert SamplerMinFilter.";
        LOG(msg);
        BREAKPOINT();
        throw std::runtime_error(msg.c_str());
    }

    GLenum OpenGLTexture2D::Convert(SamplerMagFilter samplerMagFilter)
    {
          if(samplerMagFilter == SamplerMagFilter::LINEAR)
        {
            return GL_LINEAR;
        }
        else if(samplerMagFilter == SamplerMagFilter::NEAREST)
        {
            return GL_NEAREST;
        }

        std::string msg = "OpenGLTexture2D::Convert: Unable to convert SamplerMagFilter.";
        LOG(msg);
        BREAKPOINT();
        throw std::runtime_error(msg.c_str());
    }

    void OpenGLTexture2D::Initialize()
    {
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);

        GLenum format = Convert(m_format);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_imageData->Width, m_imageData->Height, 0, format, GL_UNSIGNED_BYTE, m_imageData->Data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Convert(m_minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Convert(m_magFilter));

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture2D::Dispose()
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
            std::string msg = "OpenGLTexture2D::Convert: Unknown texture format.";
            BREAKPOINT();
            LOG(msg);
            throw std::runtime_error(msg.c_str());
        }
    }
}

#endif
