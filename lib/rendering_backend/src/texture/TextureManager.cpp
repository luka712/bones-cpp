#include "texture/TextureManager.hpp"

namespace bns
{
    TextureOptions::TextureOptions()
    {
        TextureUsageFlags = TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST;
        Format = TextureFormat::RGBA_8_Unorm;
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

        Texture2D *texture = CreateTexture(imageData, options.TextureUsageFlags, options.Format, key);
        delete imageData;

        return texture;
    }

    Texture2D *TextureManager::CreateTexture(ImageData *imageData, i32 textureUsageFlags, TextureFormat format, std::string key )
    {
        // Here texture 2d will be of type WebGPUTexture2D, MetalTexture2D etc.
        Texture2D *texture = CreateBackendImplTexture(imageData, textureUsageFlags, format);

        texture->Initialize();

        if (key != "")
        {
            if (m_textureCache.at(key) != nullptr)
            {
                // Destroy the texture.
                m_textureCache[key]->Release();
                auto ptr = m_textureCache[key];
                delete ptr;
            }

            m_textureCache[key] = texture;
        }

        return texture;
    }

    Texture2D *TextureManager::CreateEmpty(u32 width, u32 height, i32 textureUsageFlags, TextureFormat format)
    {
        // image data is done in this way so that it gets automatically deleted
        ImageData imageData;
        imageData.Width = width;
        imageData.Height = height;
        imageData.Data = new u8[width * height * 4];

        return CreateTexture(&imageData, textureUsageFlags, format);
    }
}
