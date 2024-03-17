#if USE_OPENGL

#include <stdexcept>
#include "texture/bns_opengl_texture2d.hpp"
#include <vector>
#include "bns_opengl_util.hpp"

namespace bns
{
    OpenGLTexture2D::OpenGLTexture2D(ImageData *imageData, TextureUsage textureUsage, TextureFormat format, SamplerMinFilter samplerMinFilter,
                                     SamplerMagFilter samplerMagFilter)
        : Texture2D(imageData->Width, imageData->Height, textureUsage, format, samplerMinFilter, samplerMagFilter), m_imageData(imageData)
    {
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
    }

    void OpenGLTexture2D::Initialize()
    {
        Texture = OpenGLUtil::Texture.CreateTexture2D(
            m_imageData->Width, m_imageData->Height, m_imageData->Data,
            "",
            m_format,
            m_minFilter, m_magFilter);
    }

    void OpenGLTexture2D::Dispose()
    {
        glDeleteTextures(1, &Texture);
    }

    OpenGLTexture2D *OpenGLTexture2D::CreateEmpty(i32 width, i32 height)
    {
        std::vector<u32> data(width * height, 0);
        for (u32 i = 0; i < data.size(); i++)
        {
            data[i] = 0xFFFFFFFF;
        }

        ImageData imageData = ImageData(data.data(), width, height, 4);
        OpenGLTexture2D *texture = new OpenGLTexture2D(&imageData,
                                                       TextureUsage::None,
                                                       TextureFormat::BGRA_8_Unorm,
                                                       SamplerMinFilter::LINEAR, SamplerMagFilter::LINEAR);

        texture->Initialize();

        return texture;
    }
}

#endif
