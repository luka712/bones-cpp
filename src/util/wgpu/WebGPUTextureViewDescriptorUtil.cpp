#include "util/wgpu/WebGPUTextureViewDescriptorUtil.hpp"

namespace bns
{
    WGPUTextureViewDescriptor WebGPUTextureViewDescriptorUtil::CreateDefault()
    {
        WGPUTextureViewDescriptor descriptor = {};
        descriptor.nextInChain = nullptr;
        descriptor.dimension = WGPUTextureViewDimension::WGPUTextureViewDimension_2D;
        descriptor.format = WGPUTextureFormat::WGPUTextureFormat_RGBA8Unorm;
        descriptor.baseMipLevel = 0;
        descriptor.mipLevelCount = 1;
        descriptor.baseArrayLayer = 0;
        descriptor.arrayLayerCount = 1;
        descriptor.aspect = WGPUTextureAspect::WGPUTextureAspect_All;
        return descriptor;
    }
}