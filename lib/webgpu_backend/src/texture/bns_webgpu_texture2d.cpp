#include "texture/bns_webgpu_texture2d.hpp"
#include "renderer/bns_webgpu_renderer.hpp"
#include <stdexcept>

namespace bns
{
    WebGPUTexture2D::WebGPUTexture2D(Renderer* renderer, ImageData *imageData, TextureUsage textureUsage, TextureFormat format)
        : Texture2D(imageData->Width, imageData->Height, textureUsage, format),
          m_imageData(imageData)
    {
        m_renderer = static_cast<WebGPURenderer*>(renderer);
        m_lifecycleState = LifecycleState::Created;
    }

    WebGPUTexture2D::~WebGPUTexture2D()
    {
        LOG("WebGPUTexture2D::~WebGPUTexture2D()");
        Dispose();
    }

    WGPUTextureUsage WebGPUTexture2D::Convert(TextureUsage textureUsage) const
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
        else if(textureUsage == TextureUsage::CopyDst_TextureBinding)
        {
            usage |= WGPUTextureUsage_CopyDst | WGPUTextureUsage_TextureBinding;
        }
        else if(textureUsage == TextureUsage::CopyDst_CopySrc_TextureBinding_RenderAttachment)
        {
            usage |= WGPUTextureUsage_CopyDst | WGPUTextureUsage_CopySrc | WGPUTextureUsage_TextureBinding | WGPUTextureUsage_RenderAttachment;
        }
        else
        {
            throw std::runtime_error("WebGPUTexture2D::Convert: Unknown texture usage.");
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

    WGPUFilterMode WebGPUTexture2D::Convert(SamplerMinFilter minFilter) const
    {
        switch (minFilter)
        {
        case SamplerMinFilter::NEAREST:
            return WGPUFilterMode_Nearest;
        case SamplerMinFilter::LINEAR:
            return WGPUFilterMode_Linear;
        default:
            throw std::runtime_error("Unknown min filter.");
        }
    }

    WGPUFilterMode WebGPUTexture2D::Convert(SamplerMagFilter magFilter) const
    {
        switch (magFilter)
        {
        case SamplerMagFilter::NEAREST:
            return WGPUFilterMode_Nearest;
        case SamplerMagFilter::LINEAR:
            return WGPUFilterMode_Linear;
        default:
            throw std::runtime_error("Unknown mag filter.");
        }
    }

    void WebGPUTexture2D::CreateTexture()
    {
        WGPUDevice device = m_renderer->GetDevice();

        WGPUTextureDescriptor textureDescriptor = {};
        textureDescriptor.sampleCount = 1;
        textureDescriptor.mipLevelCount = 1;
        textureDescriptor.dimension = WGPUTextureDimension_2D;
        textureDescriptor.size = {(u32)m_imageData->Width, (u32)m_imageData->Height, 1};

        // convert convers our custom format to the WebGPU format
        textureDescriptor.format = Convert(m_format);
        textureDescriptor.usage = Convert(m_textureUsage);

        Texture = wgpuDeviceCreateTexture(device, &textureDescriptor);

        if(Texture == nullptr)
        {
            std::string msg = "WebGPUTexture2D::CreateTexture: Failed to create texture.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        LOG("WebGPUTexture2D::CreateTexture: Texture created.")
    }

    void WebGPUTexture2D::WriteToTexture()
    {
        WGPUQueue queue = m_renderer->GetQueue();

        // Arguments telling which part of the texture we upload to
        WGPUImageCopyTexture destination;
        destination.texture = Texture;
        destination.mipLevel = 0;
        destination.origin = {0, 0, 0};
        destination.aspect = WGPUTextureAspect_All; // only relevant for depth/stencil textures

        // Arguments telling how the C++ side pixel memory is laid out
        WGPUTextureDataLayout source;
        source.offset = 0;
        source.bytesPerRow = 4 * m_imageData->Width;
        source.rowsPerImage = m_imageData->Height;

        WGPUExtent3D size = {static_cast<u32>(m_imageData->Width), static_cast<u32>(m_imageData->Height), 1};
        size_t dataSize = m_imageData->GetSize();
        wgpuQueueWriteTexture(queue, &destination, m_imageData->Data, dataSize, &source, &size);

        LOG("WebGPUTexture2D::WriteToTexture: Texture written.")
    }

    void WebGPUTexture2D::CreateSampler()
    {
        WGPUSamplerDescriptor samplerDescriptor = {};
        samplerDescriptor.addressModeU = WGPUAddressMode_Repeat;
        samplerDescriptor.addressModeV = WGPUAddressMode_Repeat;
        samplerDescriptor.addressModeW = WGPUAddressMode_Repeat;
        samplerDescriptor.minFilter = Convert(m_minFilter);
        samplerDescriptor.magFilter = Convert(m_magFilter);
        samplerDescriptor.lodMinClamp = 0.0f;
        samplerDescriptor.lodMaxClamp = 0.0f;
        samplerDescriptor.maxAnisotropy = 1;
        samplerDescriptor.compare = WGPUCompareFunction_Undefined;
        Sampler = wgpuDeviceCreateSampler(m_renderer->GetDevice(), &samplerDescriptor);

        if(Sampler == nullptr)
        {
            std::string msg = "WebGPUTexture2D::CreateSampler: Failed to create sampler.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        LOG("WebGPUTexture2D::CreateSampler: Sampler created.")
    }

    void WebGPUTexture2D::Initialize()
    {
        m_lifecycleState = LifecycleState::Initialized;

        CreateTexture();
        WriteToTexture();
        CreateSampler();
    }

    WGPUTextureView WebGPUTexture2D::CreateView() const
    {
        WGPUTextureViewDescriptor textureViewDesc = WebGPUUtil::TextureViewDescriptor.Create("Texture view: " + std::to_string(m_id));
        textureViewDesc.format = Convert(m_format);
        WGPUTextureView textureView = wgpuTextureCreateView(Texture, &textureViewDesc);
        return textureView;
    }

    void WebGPUTexture2D::Dispose()
    {
        m_lifecycleState = LifecycleState::Released;
        wgpuSamplerRelease(Sampler);
        wgpuTextureRelease(Texture);
    }
}