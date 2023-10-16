#include "textures/TextureManager.hpp"
#include "Framework.hpp"

#if __APPLE__ && USE_METAL
#include "textures/metal/MetalTexture2D.hpp"
#else
#include "textures/wgpu/WebGPUTexture2D.hpp"
#endif

namespace bns
{
    TextureOptions::TextureOptions()
    {
        TextureUsageFlags = TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST;
        Format = TextureFormat::RGBA_8_Unorm;
    }

    TextureManager::TextureManager(Framework &framework)
        : m_framework(framework)
    {
    }

    Texture2D *TextureManager::LoadTexture2D(std::string path, std::string key, TextureOptions *textureOptions)
    {
        ImageData *imageData = m_framework.GetImageLoader().LoadImage(path);

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
        Texture2D *texture = nullptr;
#if __APPLE__ && USE_METAL
        texture = new MetalTexture2D(m_framework, imageData, textureUsageFlags, format);
#else
        texture = new WebGPUTexture2D(m_framework, imageData, textureUsageFlags, format);
#endif
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

        u8 data[width * height * 4];
        imageData.Data = &data;

        return CreateTexture(&imageData, textureUsageFlags, format);
    }
}
