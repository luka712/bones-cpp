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

    WGPUBuffer WebGPUBufferUtil::CreateIndexBuffer(WGPUDevice device,
                                                   std::vector<u16> data,
                                                   std::string label)
    {
        size_t byteSize = data.size() * sizeof(u16);

        WGPUBufferDescriptor bufferDescriptor;
        bufferDescriptor.label = label.c_str();
        bufferDescriptor.size = data.size() * sizeof(u16);
        bufferDescriptor.usage = WGPUBufferUsage_Index;
        bufferDescriptor.mappedAtCreation = true;
        bufferDescriptor.nextInChain = nullptr;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &bufferDescriptor);

        memcpy(wgpuBufferGetMappedRange(buffer, 0, byteSize), data.data(), byteSize);
        wgpuBufferUnmap(buffer);

        return buffer;
    }

    WGPUBuffer WebGPUBufferUtil::CreateIndexBuffer(WGPUDevice device,
                                                   std::vector<u32> data,
                                                   std::string label)
    {
        size_t byteSize = data.size() * sizeof(u32);

        WGPUBufferDescriptor bufferDescriptor;
        bufferDescriptor.label = label.c_str();
        bufferDescriptor.size = data.size() * sizeof(u32);
        bufferDescriptor.usage = WGPUBufferUsage_Index;
        bufferDescriptor.mappedAtCreation = true;
        bufferDescriptor.nextInChain = nullptr;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &bufferDescriptor);

        memcpy(wgpuBufferGetMappedRange(buffer, 0, byteSize), data.data(), byteSize);
        wgpuBufferUnmap(buffer);

        return buffer;
    }
}