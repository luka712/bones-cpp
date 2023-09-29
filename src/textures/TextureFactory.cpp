#include "textures/TextureFactory.hpp"

#if __APPLE__ && USE_METAL
#include "textures/metal/MetalTexture2D.hpp"
#else
#include "textures/wgpu/WebGPUTexture2D.hpp"
#endif

namespace bns
{
    TextureFactory::TextureFactory(const Framework &framework)
        : m_framework(framework)
    {
    }

    Texture2D *TextureFactory::CreateTexture(ImageData *imageData, i32 textureUsageFlags, TextureFormat format)
    {
        Texture2D *texture = nullptr;
#if __APPLE__ && USE_METAL
        texture = new MetalTexture2D(m_framework, imageData, textureUsageFlags, format);
#else
        texture = new WebGPUTexture2D(m_framework, imageData, textureUsageFlags, format);
#endif
        texture->Initialize();
        return texture;
    }

    Texture2D *TextureFactory::CreateEmpty(u32 width, u32 height, i32 textureUsageFlags, TextureFormat format)
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
