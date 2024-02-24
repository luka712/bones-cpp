#include "texture/bns_texture_manager.hpp"

namespace bns
{
    TextureOptions::TextureOptions()
    {
        TextureUsage = TextureUsage::CopyDst_TextureBinding;
        Format = TextureFormat::RGBA_8_Unorm;
        MinFilter = SamplerMinFilter::LINEAR;
        MagFilter = SamplerMagFilter::LINEAR;
    }

    TextureManager::TextureManager(ImageLoader *imageLoader)
        : m_imageLoader(imageLoader)
    {
    }

    Texture2D *TextureManager::LoadTexture2D(std::string path, std::string key, TextureOptions *textureOptions)
    {
        ImageData *imageData = m_imageLoader->LoadImage(path);

        TextureOptions options;
        if (textureOptions != nullptr)
        {
            options = *textureOptions;
        }

        Texture2D *texture = CreateTexture(imageData, options.TextureUsage, options.Format, options.MinFilter, options.MagFilter, key);
        delete imageData;

        return texture;
    }

    Texture2D *TextureManager::CreateTexture(ImageData *imageData, TextureUsage textureUsage, TextureFormat format,
                                             SamplerMinFilter samplerMinFilter, SamplerMagFilter samplerMagFilter,
                                             std::string key)
    {
        // Here texture 2d will be of type WebGPUTexture2D, MetalTexture2D etc.
        Texture2D *texture = CreateBackendImplTexture(imageData, textureUsage, format, samplerMinFilter, samplerMagFilter);

        texture->Initialize();

        if (key != "")
        {
            if (m_textureCache.count(key) > 0)
            {
                // Destroy the texture.
                m_textureCache[key]->Dispose();
                Texture2D *ptr = m_textureCache[key];
                delete ptr;
            }

            m_textureCache[key] = texture;
        }

        return texture;
    }

    Texture2D *TextureManager::CreateEmpty(u32 width, u32 height, TextureUsage textureUsage, TextureFormat format)
    {
        // image data is done in this way so that it gets automatically deleted
        ImageData imageData;
        imageData.Width = width;
        imageData.Height = height;
        imageData.Data = new u8[width * height * 4];

        return CreateTexture(&imageData, textureUsage, format);
    }
}
