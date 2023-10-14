#include "textures/metal/MetalTexture2D.hpp"
#include "Framework.hpp"

namespace bns
{
    MTL::PixelFormat MetalTexture2D::Convert(TextureFormat format) const
    {
        switch (format)
        {
        case TextureFormat::RGBA_8_Unorm:
            return MTL::PixelFormatRGBA8Unorm;
        case TextureFormat::BGRA_8_Unorm:
            return MTL::PixelFormatBGRA8Unorm;
        default:
            throw std::runtime_error("Unknown texture format");
        }
    }

    MTL::TextureUsage MetalTexture2D::Convert(i32 textureUsageFlags) const
    {
        i32 usage = MTL::TextureUsageUnknown;

        if (textureUsageFlags & TextureUsage::COPY_DST)
        {
            usage |= MTL::TextureUsageShaderRead;
        }
        if (textureUsageFlags & TextureUsage::COPY_SRC)
        {
            usage |= MTL::TextureUsageShaderWrite;
        }
        if (textureUsageFlags & TextureUsage::TEXTURE_BINDING)
        {
            usage |= MTL::TextureUsageShaderRead;
        }
        if (textureUsageFlags & TextureUsage::TEXTURE_STORAGE)
        {
            usage |= MTL::TextureUsageShaderRead;
        }
        if (textureUsageFlags & TextureUsage::RENDER_ATTACHMENT)
        {
            usage |= MTL::TextureUsageRenderTarget;
        }

        return static_cast<MTL::TextureUsage>(usage);
    }

    MetalTexture2D::MetalTexture2D(const Framework &framework, ImageData *imageData, i32 textureUsageFlags, TextureFormat format)
        : Texture2D(imageData->Width, imageData->Height, textureUsageFlags, format), m_framework(framework), m_imageData(imageData)
    {
    }

    void MetalTexture2D::Initialize()
    {
        MTL::Device *device = m_framework.Context.MetalDevice;

        NS::UInteger texWidth = m_imageData->Width;
        NS::UInteger texHeight = m_imageData->Height;

        MTL::PixelFormat pixelFormat = Convert(m_format);
        MTL::TextureUsage textureUsage = Convert(m_textureUsageFlags);

        MTL::TextureDescriptor *textureDescriptor = MTL::TextureDescriptor::alloc()->init();
        textureDescriptor->setTextureType(MTL::TextureType2D);
        textureDescriptor->setPixelFormat(pixelFormat);
        textureDescriptor->setWidth(texWidth);
        textureDescriptor->setHeight(texHeight);
        textureDescriptor->setStorageMode(MTL::StorageModeManaged);
        textureDescriptor->setUsage(textureUsage);

        MTL::Texture *texture = device->newTexture(textureDescriptor);
        // textureDescriptor->release();

        MTL::Region region;
        region.origin = {0, 0, 0};
        region.size = {texWidth, texHeight, 1};

        // bytes per row
        NS::Integer bytesPerRow = 4 * m_imageData->Width;

        texture->replaceRegion(region, 0, m_imageData->Data, bytesPerRow);

        MTL::SamplerDescriptor *samplerDescriptor = MTL::SamplerDescriptor::alloc()->init();

        Sampler = device->newSamplerState(samplerDescriptor);
        //  samplerDescriptor->release();

        Texture = texture;
    }

    void MetalTexture2D::Release()
    {
        Sampler->release();
        Texture->release();
    }

}
