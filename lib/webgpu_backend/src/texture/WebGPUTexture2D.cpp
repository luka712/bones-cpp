#include "texture/WebGPUTexture2D.hpp"

namespace bns
{
    WebGPUTexture2D::WebGPUTexture2D(WGPUDevice device, ImageData *imageData, i32 textureUsageFlags, TextureFormat format)
        : Texture2D(imageData->Width, imageData->Height, textureUsageFlags, format),
          m_device(device),
          m_imageData(imageData)
    {
    }

    WGPUTextureUsage WebGPUTexture2D::Convert(i32 textureUsageFlags) const
    {
        i32 usage = WGPUTextureUsage_None;

        if (textureUsageFlags & TextureUsage::COPY_DST)
        {
            usage |= WGPUTextureUsage_CopyDst;
        }
        if (textureUsageFlags & TextureUsage::COPY_SRC)
        {
            usage |= WGPUTextureUsage_CopySrc;
        }
        if (textureUsageFlags & TextureUsage::TEXTURE_BINDING)
        {
            usage |= WGPUTextureUsage_TextureBinding;
        }
        if (textureUsageFlags & TextureUsage::TEXTURE_STORAGE)
        {
            usage |= WGPUTextureUsage_StorageBinding;
        }
        if (textureUsageFlags & TextureUsage::RENDER_ATTACHMENT)
        {
            usage |= WGPUTextureUsage_RenderAttachment;
        }

        return static_cast<WGPUTextureUsage>(usage);
    }

    WGPUTextureFormat WebGPUTexture2D::Convert(TextureFormat format) const
    {
        switch (format)
        {
        case TextureFormat::RGBA_8_Unorm:
            return WGPUTextureFormat_RGBA8Unorm;
        case TextureFormat::BGRA_8_Unorm:
            return WGPUTextureFormat_BGRA8Unorm;
        default:
            throw std::runtime_error("Unknown texture format");
        }
    }

    void WebGPUTexture2D::Initialize()
    {
        m_lifecycleState = LifecycleState::Initialized;
        WGPUQueue queue = wgpuDeviceGetQueue(m_device);

        WGPUTextureDescriptor textureDescriptor = {};
        textureDescriptor.sampleCount = 1;
        textureDescriptor.mipLevelCount = 1;
        textureDescriptor.dimension = WGPUTextureDimension_2D;
        textureDescriptor.size = {(u32)m_imageData->Width, (u32)m_imageData->Height, 1};

        // convert convers our custom format to the WebGPU format
        textureDescriptor.format = Convert(m_format);
        textureDescriptor.usage = Convert(m_textureUsageFlags);

        WGPUTexture texture = wgpuDeviceCreateTexture(m_device, &textureDescriptor);

        // Arguments telling which part of the texture we upload to
        WGPUImageCopyTexture destination;
        destination.texture = texture;
        destination.mipLevel = 0;
        destination.origin = {0, 0, 0};
        destination.aspect = WGPUTextureAspect_All; // only relevant for depth/stencil textures

        // Arguments telling how the C++ side pixel memory is laid out
        WGPUTextureDataLayout source;
        source.offset = 0;
        source.bytesPerRow = 4 * textureDescriptor.size.width;
        source.rowsPerImage = textureDescriptor.size.height;

        size_t size = m_imageData->Width * m_imageData->Height * 4;
        wgpuQueueWriteTexture(queue, &destination, m_imageData->Data, size, &source, &textureDescriptor.size);

        Texture = texture;

        WGPUSamplerDescriptor samplerDescriptor = {};
        samplerDescriptor.addressModeU = WGPUAddressMode_Repeat;
        samplerDescriptor.addressModeV = WGPUAddressMode_Repeat;
        samplerDescriptor.addressModeW = WGPUAddressMode_Repeat;
        samplerDescriptor.minFilter = WGPUFilterMode_Linear;
        samplerDescriptor.magFilter = WGPUFilterMode_Linear;
        samplerDescriptor.lodMinClamp = 0.0f;
        samplerDescriptor.lodMaxClamp = 0.0f;
        samplerDescriptor.maxAnisotropy = 1;
        samplerDescriptor.compare = WGPUCompareFunction_Undefined;
        WGPUSampler sampler = wgpuDeviceCreateSampler(m_device, &samplerDescriptor);

        Sampler = sampler;
    }

    void WebGPUTexture2D::Release()
    {
        m_lifecycleState = LifecycleState::Released;
        wgpuSamplerRelease(Sampler);
        wgpuTextureRelease(Texture);
    }
}