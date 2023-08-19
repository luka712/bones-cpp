#include "textures/wgpu/WebGPUTexture2D.hpp"
#include "Framework.hpp"

namespace bns
{
    WebGPUTexture2D::WebGPUTexture2D(Framework &framework, ImageData *imageData)
        : Texture2D(imageData->Width, imageData->Height), m_framework(framework), m_imageData(imageData)
    {
    
    }

    void WebGPUTexture2D::Initialize()
    {
        WGPUDevice device = m_framework.Context.WebGPUDevice;
        WGPUQueue queue = wgpuDeviceGetQueue(device);

        WGPUTextureDescriptor textureDescriptor = {};
        textureDescriptor.sampleCount = 1;
        textureDescriptor.mipLevelCount = 1;
        textureDescriptor.dimension = WGPUTextureDimension_2D;
        textureDescriptor.size = {(u32)m_imageData->Width, (u32)m_imageData->Height, 1};
        textureDescriptor.format = WGPUTextureFormat_RGBA8Unorm; // TODO: maybe passed from image data
        textureDescriptor.usage = WGPUTextureUsage_CopyDst | WGPUTextureUsage_TextureBinding;

        WGPUTexture texture = wgpuDeviceCreateTexture(device, &textureDescriptor);

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
        WGPUSampler sampler = wgpuDeviceCreateSampler(device, &samplerDescriptor);

        Sampler = sampler;
    }
}