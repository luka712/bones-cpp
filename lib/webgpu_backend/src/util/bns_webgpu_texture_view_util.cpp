#if USE_WEBGPU

#include "util/bns_webgpu_texture_view_util.hpp"
#include <stdexcept>
#include "bns_webgpu_util.hpp"

namespace bns
{
    WGPUTextureView WebGPUTextureViewUtil::Create(WGPUTexture texture, TextureFormat textureFormat, std::string label)
    {
        WGPUTextureViewDescriptor descriptor = {};
        descriptor.format = WebGPUUtil::Converter.Convert(textureFormat);
        descriptor.nextInChain = nullptr;
        descriptor.label = label.c_str();
        descriptor.dimension = WGPUTextureViewDimension_2D;
        descriptor.baseMipLevel = 0;
        descriptor.mipLevelCount = 1;
        descriptor.baseArrayLayer = 0;
        descriptor.arrayLayerCount = 1;
        descriptor.aspect = WGPUTextureAspect_All;

        WGPUTextureView textureView = wgpuTextureCreateView(texture, &descriptor);

        if(textureView == nullptr)
        {
            std::string msg = "WebGPUTextureViewUtil::Create: Failed to create texture view.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return textureView;
    }

    void WebGPUTextureViewUtil::Dispose(WGPUTextureView textureView)
    {
        if(textureView != nullptr)
        {
            wgpuTextureViewRelease(textureView);
        }
    }
}

#endif