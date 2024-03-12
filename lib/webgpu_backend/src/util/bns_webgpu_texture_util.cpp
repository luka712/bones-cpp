#if USE_WEBGPU

#include "util/bns_webgpu_texture_util.hpp"
#include "bns_webgpu_util.hpp"

namespace bns
{
    WGPUTexture WebGPUTextureUtil::Create(WGPUDevice device, u32 width, u32 height, TextureFormat format, TextureUsage textureUsage)
    {
        WGPUTextureDescriptor textureDescriptor = {};
        textureDescriptor.nextInChain = nullptr;
        textureDescriptor.sampleCount = 1;
        textureDescriptor.mipLevelCount = 1;
        textureDescriptor.dimension = WGPUTextureDimension_2D;
        textureDescriptor.size = {width, height, 1};

        // convert convers our custom format to the WebGPU format
        textureDescriptor.format = WebGPUUtil::Converter.Convert(format);
        textureDescriptor.usage = WebGPUUtil::Converter.Convert(textureUsage);

        WGPUTexture texture = wgpuDeviceCreateTexture(device, &textureDescriptor);

        if (texture == nullptr)
        {
            std::string msg = "WebGPUTexture2D::CreateTexture: Failed to create texture.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
        
        return texture;
    }

    WGPUTexture WebGPUTextureUtil::Create(WGPUDevice device, WGPUQueue queue, u32 width, u32 height, TextureFormat format, TextureUsage textureUsage, void *data)
    {
        WGPUTexture texture = Create(device, width, height, format, textureUsage);

        // Arguments telling which part of the texture we upload to
        WGPUImageCopyTexture destination;
        destination.nextInChain = nullptr;
        destination.texture = texture;
        destination.mipLevel = 0;
        destination.origin = {0, 0, 0};
        destination.aspect = WGPUTextureAspect_All; // only relevant for depth/stencil textures

        // Arguments telling how the C++ side pixel memory is laid out
        WGPUTextureDataLayout source;
        source.nextInChain = nullptr;
        source.offset = 0;
        source.bytesPerRow = 4 * width;
        source.rowsPerImage = height;

        WGPUExtent3D size = {width, height, 1};
        size_t dataSize = width * height * 4;
        wgpuQueueWriteTexture(queue, &destination, data, dataSize, &source, &size);
       

        return texture;
    }
}

#endif
