#include "util/WebGPUTextureViewDescriptorUtil.hpp"

namespace bns
{
    WGPUTextureViewDescriptor WebGPUTextureViewDescriptorUtil::Create(std::string label)
    {
        WGPUTextureViewDescriptor descriptor = {};
        descriptor.nextInChain = nullptr;
        descriptor.label = label.c_str();
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
