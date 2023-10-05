#ifndef BNS_WEBGPU_UTIL

#define BNS_WEBGPU_UTIL

#include "util/wgpu/WebGPUBufferUtil.hpp"
#include "util/wgpu/WebGPUFragmentStateUtil.hpp"
#include "util/wgpu/WebGPUBindGroupLayoutDescriptorUtil.hpp"
#include "util/wgpu/WebGPUBindGroupLayoutEntryUtil.hpp"
#include "util/wgpu/WebGPUBindGroupEntryUtil.hpp"
#include "util/wgpu/WebGPUPipelineLayoutDescriptorUtil.hpp"
#include "util/wgpu/WebGPUBindGroupDescriptorUtil.hpp"
#include "util/wgpu/WebGPUTextureViewDescriptorUtil.hpp"
#include "util/wgpu/WebGPUBlendStateUtil.hpp"
#include "util/wgpu/WebGPURenderPassColorAttachmentUtil.hpp"
#include "util/wgpu/WebGPURenderPassDescriptorUtil.hpp"
#include "util/wgpu/WebGPUShaderModuleUtil.hpp"
#include "util/wgpu/WebGPUVertexBufferLayoutUtil.hpp"
#include "util/wgpu/WebGPURenderPipelineDescriptorUtil.hpp"
#include "util/wgpu/WebGPUCommandEncoderUtil.hpp"


namespace bns
{
    struct WebGPUUtil final
    {
        static WebGPUBufferUtil Buffer;
        static WebGPUFragmentStateUtil FragmentState;
        static WebGPUBindGroupLayoutDescriptorUtil BindGroupLayoutDescriptor;
        static WebGPUBindGroupLayoutEntryUtil BindGroupLayoutEntry;
        static WebGPUBindGroupEntryUtil BindGroupEntry;
        static WebGPUPipelineLayoutDescriptorUtil PipelineLayoutDescriptor;
        static WebGPUBindGroupDescriptorUtil BindGroupDescriptor;
        static WebGPUTextureViewDescriptorUtil TextureViewDescriptor;
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