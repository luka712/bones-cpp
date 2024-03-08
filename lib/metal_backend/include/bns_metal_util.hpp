#if USE_METAL

#ifndef BNS_METAL_UTIL

#define BNS_METAL_UTIL

#include "util/bns_metal_converter.hpp"
#include "util/bns_metal_buffer_util.hpp"
#include "util/bns_metal_library_util.hpp"
#include "util/bns_metal_render_pipeline_state_util.hpp"

#include "util/MetalVertexBufferLayoutUtil.hpp"
#include "util/MetalRenderPipelineDescriptorUtil.hpp"
#include "util/MetalRenderPipelineColorAttachmentDescriptorUtil.hpp"

namespace bns
{
    /// @brief The Metal utility class. Works with Metal specific types.
    struct MetalUtil
    {
        /// @brief The Metal specific types converter.
        static MetalConverter Converter;

        /// @brief The Metal buffer utility.
        static MetalBufferUtil Buffer;

        /// @brief The Metal library utility.
        static MetalLibraryUtil Library;

        /// @brief The Metal render pipeline state utility.
        static MetalRenderPipelineStateUtil RenderPipelineState;


        static MetalVertexBufferLayoutUtil VertexBufferLayout;
        static MetalRenderPipelineDescriptorUtil RenderPipelineDescriptor;
        static MetalRenderPipelineColorAttachmentDescriptorUtil RenderPipelineColorAttachmentDescriptor;
    };
}

#endif

#endif
