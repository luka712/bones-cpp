#ifndef BNS_WEBGPU_TEXTURE_VIEW_DESCRIPTOR_HPP
#define BNS_WEBGPU_TEXTURE_VIEW_DESCRIPTOR_HPP

#include <webgpu/webgpu.h>

// TODO: TExture view descriptor util
namespace bns
{
    struct WebGPUTextureViewDescriptorUtil final
    {
        /**
         * @brief Create a default texture view descriptor
         * @return WGPUTextureViewDescriptor
        */
        static WGPUTextureViewDescriptor CreateDefault();
    };
}

#endif