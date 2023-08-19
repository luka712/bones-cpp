#ifndef BNS_METAL_UTIL_HPP

#define BNS_METAL_UTIL_HPP

#include "util/metal/MetalBufferUtil.hpp"
#include "util/metal/MetalLibraryUtil.hpp"
#include "util/metal/MetalVertexBufferLayoutUtil.hpp"
#include "util/metal/MetalRenderPipelineDescriptorUtil.hpp"


namespace bns
{
    struct MetalUtil final
    {
        static MetalBufferUtil Buffer;
        static MetalLibraryUtil Library;
        static MetalVertexBufferLayoutUtil VertexBufferLayout;
        static MetalRenderPipelineDescriptorUtil RenderPipelineDescriptor;
    };
}

#endif // BNS_METAL_UTIL_HPP