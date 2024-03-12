#if USE_WEBGPU

#include "util/bns_webgpu_converter.hpp"
#include <stdexcept>

namespace bns
{
    WGPUTextureFormat WebGPUConverter::Convert(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::RGBA_8_Unorm:
            return WGPUTextureFormat_RGBA8Unorm;
        case TextureFormat::BGRA_8_Unorm:
            return WGPUTextureFormat_BGRA8Unorm;
        default:
            BREAKPOINT();
            std::string msg = "WebGPUConverter::Convert: Unknown texture format.";
            LOG(msg);
            throw std::runtime_error(msg);
        }
    }

    WGPUTextureUsage WebGPUConverter::Convert(TextureUsage textureUsage)
    {
        i32 usage = WGPUTextureUsage_None;

        if (textureUsage == TextureUsage::CopyDst)
        {
            usage |= WGPUTextureUsage_CopyDst;
        }
        else if (textureUsage == TextureUsage::CopySrc)
        {
            usage |= WGPUTextureUsage_CopySrc;
        }
        else if (textureUsage == TextureUsage::TextureBinding)
        {
            usage |= WGPUTextureUsage_TextureBinding;
        }
        else if (textureUsage == TextureUsage::TextureStorage)
        {
            usage |= WGPUTextureUsage_StorageBinding;
        }
        else if (textureUsage == TextureUsage::RenderAttachment)
        {
            usage |= WGPUTextureUsage_RenderAttachment;
        }
        else if (textureUsage == TextureUsage::CopyDst_TextureBinding)
        {
            usage |= WGPUTextureUsage_CopyDst | WGPUTextureUsage_TextureBinding;
        }
        else if (textureUsage == TextureUsage::CopyDst_CopySrc_TextureBinding_RenderAttachment)
        {
            usage |= WGPUTextureUsage_CopyDst | WGPUTextureUsage_CopySrc | WGPUTextureUsage_TextureBinding | WGPUTextureUsage_RenderAttachment;
        }
        else
        {
            BREAKPOINT();
            std::string msg = "WebGPUConverter::Convert: Unknown texture usage.";
            LOG(msg);
            throw std::runtime_error(msg);
        }
        return static_cast<WGPUTextureUsage>(usage);
    }
}

#endif