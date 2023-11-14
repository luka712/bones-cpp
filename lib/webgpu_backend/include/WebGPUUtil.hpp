#if USE_WEBGPU 

#ifndef BNS_WEBGPU_UTIL

#define BNS_WEBGPU_UTIL

#include "util/WebGPUTextureViewDescriptorUtil.hpp"
#include "util/WebGPUBufferUtil.hpp"
#include "util/WebGPUFragmentStateUtil.hpp"
#include "util/WebGPUBindGroupLayoutDescriptorUtil.hpp"
#include "util/WebGPUBindGroupLayoutEntryUtil.hpp"
#include "util/WebGPUBindGroupEntryUtil.hpp"
#include "util/WebGPUPipelineLayoutDescriptorUtil.hpp"
#include "util/WebGPUBindGroupDescriptorUtil.hpp"
#include "util/WebGPUBlendStateUtil.hpp"
#include "util/WebGPURenderPassColorAttachmentUtil.hpp"
#include "util/WebGPURenderPassDescriptorUtil.hpp"
#include "util/WebGPUShaderModuleUtil.hpp"
#include "util/WebGPUVertexBufferLayoutUtil.hpp"
#include "util/WebGPURenderPipelineDescriptorUtil.hpp"
#include "util/WebGPUCommandEncoderUtil.hpp"

namespace bns
{
    /// @brief The WebGPU util, holds all the utility classes that cab help with
    /// allocating and creating WebGPU resources.
    struct WebGPUUtil final
    {
        /// @brief The texture view descriptor util.
        static WebGPUTextureViewDescriptorUtil TextureViewDescriptor;

        static WebGPUBufferUtil Buffer;
        static WebGPUFragmentStateUtil FragmentState;
        static WebGPUBindGroupLayoutDescriptorUtil BindGroupLayoutDescriptor;
        static WebGPUBindGroupLayoutEntryUtil BindGroupLayoutEntry;
        static WebGPUBindGroupEntryUtil BindGroupEntry;
        static WebGPUPipelineLayoutDescriptorUtil PipelineLayoutDescriptor;
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