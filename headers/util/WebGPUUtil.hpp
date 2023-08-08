#ifndef BNS_WEBGPU_UTIL

#define BNS_WEBGPU_UTIL

#include "util/wgpu/WebGPUBufferUtil.hpp"
#include "util/wgpu/WebGPUFragmentStateUtil.hpp"
#include "util/wgpu/WebGPUBindGroupLayoutDescriptorUtil.hpp"
#include "util/wgpu/WGPUBindGroupLayoutEntryUtil.hpp"
#include "util/wgpu/WebGPUBindGroupEntryUtil.hpp"
#include "util/wgpu/WebGPUPipelineLayoutDescriptorUtil.hpp"
#include "util/wgpu/WebGPUBindGroupDescriptorUtil.hpp"
#include "util/wgpu/WebGPUTextureViewDescriptorUtil.hpp"

namespace bns
{
    struct WebGPUUtil final
    {
        static WebGPUBufferUtil Buffer;
        static WebGPUFragmentStateUtil FragmentState;
        static WebGPUBindGroupLayoutDescriptorUtil BindGroupLayoutDescriptor;
        static WGPUBindGroupLayoutEntryUtil BindGroupLayoutEntry;
        static WebGPUBindGroupEntryUtil BindGroupEntry;
        static WebGPUPipelineLayoutDescriptorUtil PipelineLayoutDescriptor;
        static WebGPUBindGroupDescriptorUtil BindGroupDescriptor;
        static WebGPUTextureViewDescriptorUtil TextureViewDescriptor;
    };
}

#endif