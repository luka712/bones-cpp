#include "util/bns_webgpu_buffer_util.hpp"

namespace bns
{
    WGPUBuffer WebGPUBufferUtil::CreateVertexBuffer(WGPUDevice device,
                                                    std::vector<f32> data,
                                                    std::string label,
                                                    WGPUBufferUsageFlags bufferUsage)
    {
        size_t byteSize = data.size() * sizeof(f32);

        // The default buffer usage. Vertex, no other usage.
        WGPUBufferUsageFlags usage = WGPUBufferUsage_Vertex;

        // Combine the usage.
        usage = usage | bufferUsage;

        WGPUBufferDescriptor bufferDescriptor = {};
        bufferDescriptor.nextInChain = nullptr;
        bufferDescriptor.label = label.c_str();
        bufferDescriptor.size = byteSize;
        bufferDescriptor.usage = usage;
        bufferDescriptor.mappedAtCreation = true;

        // Create the buffer.
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &bufferDescriptor);

        // Get pointer to gpu memory.
        void *gpuBufferPtr = wgpuBufferGetMappedRange(buffer, 0, byteSize);
        // copy to gpu memory.
        memcpy(gpuBufferPtr, data.data(), byteSize);
        // Unmap the buffer.
        wgpuBufferUnmap(buffer);

        return buffer;
    }

    WGPUBuffer WebGPUBufferUtil::CreateVertexBuffer(WGPUDevice device,
                                                    size_t byteSize,
                                                    std::string label)
    {
        WGPUBufferDescriptor bufferDescriptor = {};
        bufferDescriptor.nextInChain = nullptr;
        bufferDescriptor.label = label.c_str();
        bufferDescriptor.size = byteSize;
        bufferDescriptor.usage = WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst;
        bufferDescriptor.mappedAtCreation = false;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &bufferDescriptor);

        return buffer;
    }

    WGPUBuffer WebGPUBufferUtil::CreateUniformBuffer(WGPUDevice device,
                                                     size_t byteSize,
                                                     std::string label,
                                                     WGPUBufferUsageFlags usage)
    {
        WGPUBufferUsageFlags usageFlags = WGPUBufferUsage_Uniform;

        // Combine the usage.
        usageFlags |= usage;

        WGPUBufferDescriptor bufferDescriptor;
        bufferDescriptor.label = label.c_str();
        bufferDescriptor.size = byteSize;
        bufferDescriptor.usage = usageFlags;
        bufferDescriptor.mappedAtCreation = false;
        bufferDescriptor.nextInChain = nullptr;
        WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &bufferDescriptor);

        return buffer;
    }

    void WebGPUBufferUtil::UpdateUniformBuffer(WGPUQueue queue,
                                               WGPUBuffer buffer,
                                               size_t byteSize,
                                               void *data,
                                               size_t offset)
    {
        wgpuQueueWriteBuffer(queue, buffer, offset, data, byteSize);
    }

    void WebGPUBufferUtil::Dispose(WGPUBuffer buffer)
    {
        wgpuBufferDestroy(buffer);
    }
}