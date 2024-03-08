#if USE_METAL

#include "texture/bns_metal_texture2d.hpp"
#include "bns_metal_util.hpp"

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

        if (textureUsageFlags & TextureUsage::CopyDst)
        {
            usage |= MTL::TextureUsageShaderRead;
        }
        if (textureUsageFlags & TextureUsage::CopySrc)
        {
            usage |= MTL::TextureUsageShaderWrite;
        }
        if (textureUsageFlags & TextureUsage::TextureBinding)
        {
            usage |= MTL::TextureUsageShaderRead;
        }
        if (textureUsageFlags & TextureUsage::TextureStorage)
        {
            usage |= MTL::TextureUsageShaderRead;
        }
        if (textureUsageFlags & TextureUsage::RenderAttachment)
        {
            usage |= MTL::TextureUsageRenderTarget;
        }

        return static_cast<MTL::TextureUsage>(usage);
    }

    MetalTexture2D::MetalTexture2D(Renderer *renderer, ImageData *imageData, TextureUsage usage, TextureFormat format)
        : Texture2D(imageData->Width, imageData->Height, usage, format), m_imageData(imageData)
    {
        m_renderer = static_cast<MetalRenderer *>(renderer);
        m_device = m_renderer->GetDevice();
    }

    MetalTexture2D::~MetalTexture2D()
    {
        Dispose();
    }

    void MetalTexture2D::Initialize()
    {
        m_lifecycleState = LifecycleState::Initialized;

        NS::UInteger texWidth = m_imageData->Width;
        NS::UInteger texHeight = m_imageData->Height;

        MTL::PixelFormat pixelFormat = MetalUtil::Converter.Convert(m_format);
        MTL::TextureUsage textureUsage = MetalUtil::Converter.Convert(m_textureUsage);

        MTL::TextureDescriptor *textureDescriptor = MTL::TextureDescriptor::alloc()->init();
        textureDescriptor->setTextureType(MTL::TextureType2D);
        textureDescriptor->setPixelFormat(pixelFormat);
        textureDescriptor->setWidth(texWidth);
        textureDescriptor->setHeight(texHeight);
        textureDescriptor->setStorageMode(MTL::StorageModeManaged);
        textureDescriptor->setUsage(textureUsage);

        MTL::Texture *texture = m_device->newTexture(textureDescriptor);
        // textureDescriptor->release();

        MTL::Region region;
        region.origin = {0, 0, 0};
        region.size = {texWidth, texHeight, 1};

        // bytes per row
        NS::Integer bytesPerRow = 4 * m_imageData->Width;

        texture->replaceRegion(region, 0, m_imageData->Data, bytesPerRow);

        MTL::SamplerDescriptor *samplerDescriptor = MTL::SamplerDescriptor::alloc()->init();

        Sampler = m_device->newSamplerState(samplerDescriptor);

        Texture = texture;
    }

    void MetalTexture2D::Dispose()
    {
        m_lifecycleState = LifecycleState::Disposed;
        Sampler->release();
        Texture->release();
    }

    Texture2D *MetalTexture2D::CreateEmpty(Renderer *renderer, i32 width, i32 height)
    {
        std::vector<u8> data(width * height * 4, 255);
        for(i32 i = 0; i < width * height * 4; i++)
        {
            data[i] = 255;
        }

        ImageData imageData = ImageData(data.data(), width, height, 4);
        Texture2D* texture = new MetalTexture2D(renderer, &imageData, TextureUsage::TextureBinding, TextureFormat::BGRA_8_Unorm);
        texture->Initialize();
        imageData.Data = nullptr;

        return texture;
    }

}

#endif // USE_METAL
