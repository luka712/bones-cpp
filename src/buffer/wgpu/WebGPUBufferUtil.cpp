#include "util/wgpu/WebGPUBufferUtil.hpp"

namespace bns
{
    WGPUBuffer WebGPUBufferUtil::CreateVertexBuffer(WGPUDevice device,
                                                    std::vector<f32> data,
                                                    std::string label)
    {
        size_t byteSize = data.size() * sizeof(f32);

        WGPUBufferDescriptor bufferDescriptor;
        bufferDescriptor.label = label.c_str();
        bufferDescriptor.size = byteSize;
        bufferDescriptor.usage = WGPUBufferUsage_Vertex;
        bufferDescriptor.mappedAtCreation = true;
        bufferDescriptor.nextInChain = nullptr;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &bufferDescriptor);

        memcpy(wgpuBufferGetMappedRange(buffer, 0, byteSize), data.data(), byteSize);
        wgpuBufferUnmap(buffer);

        return buffer;
    }

    WGPUBuffer WebGPUBufferUtil::CreateVertexBuffer(WGPUDevice device,
                                  size_t byteSize,
                                  std::string label)
    {
        WGPUBufferDescriptor bufferDescriptor;
        bufferDescriptor.label = label.c_str();
        bufferDescriptor.size = byteSize;
        bufferDescriptor.usage = WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst;
        bufferDescriptor.mappedAtCreation = false;
        bufferDescriptor.nextInChain = nullptr;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &bufferDescriptor);

        return buffer;
    }

    WGPUBuffer WebGPUBufferUtil::CreateUniformBuffer(WGPUDevice device,
                                                     size_t byteSize,
                                                     std::string label)
    {
        WGPUBufferDescriptor bufferDescriptor;
        bufferDescriptor.label = label.c_str();
        bufferDescriptor.size = byteSize;
        bufferDescriptor.usage = WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst;
        bufferDescriptor.mappedAtCreation = false;
        bufferDescriptor.nextInChain = nullptr;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &bufferDescriptor);

        return buffer;
    }
}