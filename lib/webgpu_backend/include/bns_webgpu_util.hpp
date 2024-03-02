#if USE_WEBGPU 

#ifndef BNS_WEBGPU_UTIL

#define BNS_WEBGPU_UTIL

#include "util/WebGPUTextureViewDescriptorUtil.hpp"
#include "util/bns_webgpu_buffer_util.hpp"
#include "util/WebGPUFragmentStateUtil.hpp"
#include "util/WebGPUBindGroupEntryUtil.hpp"
#include "util/WebGPUBindGroupDescriptorUtil.hpp"
#include "util/WebGPUBlendStateUtil.hpp"
#include "util/WebGPURenderPassColorAttachmentUtil.hpp"
#include "util/WebGPURenderPassDescriptorUtil.hpp"
#include "util/WebGPUShaderModuleUtil.hpp"
#include "util/WebGPUVertexBufferLayoutUtil.hpp"
#include "util/WebGPURenderPipelineDescriptorUtil.hpp"
#include "util/WebGPUCommandEncoderUtil.hpp"
#include "util/bns_webgpu_bind_group_layout_util.hpp"
#include "util/bns_webgpu_pipeline_layout_util.hpp"
#include "util/bns_webgpu_render_pipeline_util.hpp"
#include "util/bns_webgpu_texture_view_util.hpp"
#include "util/bns_webgpu_converter.hpp"
#include "util/bns_webgpu_bind_group_util.hpp"

namespace bns
{
    /// @brief The WebGPU util, holds all the utility classes that cab help with
    /// allocating and creating WebGPU resources.
    struct WebGPUUtil final
    {
        /// @brief The texture view descriptor util.
        static WebGPUTextureViewDescriptorUtil TextureViewDescriptor;

        /// @brief The bind group layout util.
        static WebGPUBindGroupLayoutUtil BindGroupLayout;

        /// @brief The pipeline layout util.
        static WebGPUPipelineLayoutUtil PipelineLayout;

        /// @brief The render pipeline util.
        static WebGPURenderPipelineUtil RenderPipeline;

        /// @brief The converter util.
        static WebGPUConverter Converter;

        /// @brief The bind group util.
        static WebGPUBindGroupUtil BindGroup;

        /// @brief The texture view util.
        static WebGPUTextureViewUtil TextureView;

        static WebGPUBufferUtil Buffer;
        static WebGPUFragmentStateUtil FragmentState;
        static WebGPUBindGroupEntryUtil BindGroupEntry;
        static WebGPUBindGroupDescriptorUtil BindGroupDescriptor;
        static WebGPUBlendStateUtil BlendState;
        static WebGPURenderPassColorAttachmentUtil RenderPassColorAttachment;
        static WebGPURenderPassDescriptorUtil RenderPassDescriptor;

        /// @brief The shader module util. Utility for creating shader modules.
        static WebGPUShaderModuleUtil ShaderModule;

        /// @brief The vertex buffer layout util. Utility for creating vertex buffer layouts.
        static WebGPUVertexBufferLayoutUtil VertexBufferLayout;

        /// @brief The render pipeline descriptor util. Utility for creating render pipeline descriptors.
        static WebGPURenderPipelineDescriptorUtil RenderPipelineDescriptor;

        /// @brief The command encoder util. Utility for creating command encoders.
        /// Command encoders are used to encode GPU operations.
        /// Usually one wants to create command encoder for:
        /// - Rendering
        /// - Compute
        static WebGPUCommandEncoderUtil CommandEncoder;
    };
}

#endif

#endif // USE_WEBGPU