#if USE_METAL

#include "util/bns_metal_converter.hpp"
#include "bns_types.hpp"

namespace bns 
{
    MTL::PixelFormat MetalConverter::Convert(TextureFormat format)
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

    MTL::TextureUsage MetalConverter::Convert(TextureUsage textureUsageFlags)
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
}

#endif 