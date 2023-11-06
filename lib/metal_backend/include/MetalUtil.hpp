#ifndef BNS_METAL_UTIL_HPP

#define BNS_METAL_UTIL_HPP

#include "util/MetalBufferUtil.hpp"
#include "util/MetalLibraryUtil.hpp"
#include "util/MetalVertexBufferLayoutUtil.hpp"
#include "util/MetalRenderPipelineDescriptorUtil.hpp"
#include "util/MetalRenderPipelineColorAttachmentDescriptorUtil.hpp"


namespace bns
{
    struct MetalUtil final
    {
        static MetalBufferUtil Buffer;
        static MetalLibraryUtil Library;
        static MetalVertexBufferLayoutUtil VertexBufferLayout;
        static MetalRenderPipelineDescriptorUtil RenderPipelineDescriptor;
        static MetalRenderPipelineColorAttachmentDescriptorUtil RenderPipelineColorAttachmentDescriptor;
    };
}

#endif // BNS_METAL_UTIL_HPP