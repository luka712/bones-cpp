#if USE_WEBGPU

#ifndef BNS_WEBGPU_TEXTURE_VIEW_DESCRIPTOR_HPP
#define BNS_WEBGPU_TEXTURE_VIEW_DESCRIPTOR_HPP

#include <webgpu/webgpu.h>
#include <string>

// TODO: TExture view descriptor util
namespace bns
{
    struct WebGPUTextureViewDescriptorUtil final
    {
        /**
         * @brief Create a default texture view descriptor
         * @return WGPUTextureViewDescriptor
        */
        static WGPUTextureViewDescriptor Create(std::string label = "bns_texture_view_desc");
    };
}

#endif

#endif // USE_WEBGPU