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
    };
}

#endif