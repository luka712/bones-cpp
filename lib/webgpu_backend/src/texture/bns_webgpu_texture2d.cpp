#include "texture/bns_webgpu_texture2d.hpp"
#include "renderer/bns_webgpu_renderer.hpp"
#include <stdexcept>

namespace bns
{
    WebGPUTexture2D::WebGPUTexture2D(Renderer *renderer, ImageData *imageData, TextureUsage textureUsage, TextureFormat format)
        : Texture2D(imageData->Width, imageData->Height, textureUsage, format),
          m_imageData(imageData)
    {
        m_renderer = static_cast<WebGPURenderer *>(renderer);
        m_lifecycleState = LifecycleState::Created;
    }

    WebGPUTexture2D::~WebGPUTexture2D()
    {
        LOG("WebGPUTexture2D::~WebGPUTexture2D()");
        Dispose();
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

        if (Sampler == nullptr)
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

        WGPUDevice device = m_renderer->GetDevice();
        WGPUQueue queue = m_renderer->GetQueue();

        Texture = WebGPUUtil::Texture.Create(device, queue, m_imageData->Width, m_imageData->Height, m_format, m_textureUsage, m_imageData->Data);

        LOG("WebGPUTexture2D::CreateTexture: Texture created and written.")
        CreateSampler();
    }

    WGPUTextureView WebGPUTexture2D::CreateView(std::string label) const
    {
        WGPUTextureView textureView = WebGPUUtil::TextureView.Create(Texture, m_format, label);
        return textureView;
    }

    void WebGPUTexture2D::Dispose()
    {
        m_lifecycleState = LifecycleState::Disposed;
        wgpuSamplerRelease(Sampler);
        wgpuTextureRelease(Texture);
    }

    WebGPUTexture2D *WebGPUTexture2D::CreateEmpty(Renderer *renderer, u32 width, u32 height)
    {
        u8 *data = new u8[width * height * 4];
        for (u32 i = 0; i < width * height * 4; i++)
        {
            data[i] = 255;
        }

        ImageData *imageData = new ImageData(data, width, height, 4);
        WebGPUTexture2D *texture = new WebGPUTexture2D(renderer, imageData, TextureUsage::CopyDst_TextureBinding, TextureFormat::BGRA_8_Unorm);
        texture->Initialize();

        // delete data;
        return texture;
    }
}
