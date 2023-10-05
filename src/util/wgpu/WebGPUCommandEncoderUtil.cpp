#include "util/wgpu/WebGPUCommandEncoderUtil.hpp"

namespace bns
{
    WGPUCommandEncoder WebGPUCommandEncoderUtil::Create(WGPUDevice device, WGPUCommandEncoderDescriptor &descriptor)
    {
        return wgpuDeviceCreateCommandEncoder(device, &descriptor);
    }

    WGPUCommandEncoder WebGPUCommandEncoderUtil::Create(WGPUDevice device, std::string label)
    {
        WGPUCommandEncoderDescriptor descriptor = {};
        descriptor.nextInChain = nullptr;
        descriptor.label = label.c_str();
        return wgpuDeviceCreateCommandEncoder(device, &descriptor);
    }
}