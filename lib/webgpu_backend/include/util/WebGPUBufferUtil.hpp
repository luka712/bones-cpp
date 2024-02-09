#ifndef BNS_WEBGPU_BUFFER_UTIL_HPP

#define BNS_WEBGPU_BUFFER_UTIL_HPP

#include <webgpu/webgpu.h>
#include <vector>
#include <string>
#include "bns_types.hpp"

namespace bns
{
    class WebGPUBufferUtil final
    {
    public:
        /**
         * @brief Create a vertex buffer
         * @param device The webgpu device
         * @param data The data to be copied to the buffer
         * @param label The label of the buffer
         * @return The vertex buffer
         * @note The data is copied to the buffer
         */
        static WGPUBuffer CreateVertexBuffer(WGPUDevice device,
                                             std::vector<f32> data,
                                             std::string label);

        /**
         * @brief Create a vertex buffer
         * @param device The webgpu device
         * @param byteSize The size of the buffer in bytes
         * @param label The label of the buffer
         * @return The vertex buffer
        */
        static WGPUBuffer CreateVertexBuffer(WGPUDevice device,
                                             size_t byteSize,
                                             std::string label);

        /**
         * @brief Create a index buffer
         * @param device The webgpu device
         * @param data The data to be copied to the buffer
         * @param label The label of the buffer
         * @return The index buffer
         * @note The data is copied to the buffer
         */
        template <typename T>
        static WGPUBuffer CreateIndexBuffer(WGPUDevice device,
                                            std::vector<T> data,
                                            std::string label)
        {
            size_t byteSize = data.size() * sizeof(T);

            WGPUBufferDescriptor bufferDescriptor;
            bufferDescriptor.label = label.c_str();
            bufferDescriptor.size = data.size() * sizeof(T);
            // TODO: for copy dst create empty one, that is another overload
            bufferDescriptor.usage = WGPUBufferUsage_Index | WGPUBufferUsage_CopyDst;
            bufferDescriptor.mappedAtCreation = true;
            bufferDescriptor.nextInChain = nullptr;
            WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &bufferDescriptor);

            memcpy(wgpuBufferGetMappedRange(buffer, 0, byteSize), data.data(), byteSize);
            wgpuBufferUnmap(buffer);

            return buffer;
        }

        /**
         * @brief Create a uniform buffer
         * @param device The webgpu device
         * @param byteSize The size of the buffer in bytes
         * @param label The label of the buffer
         * @return The uniform buffer
        */
        static WGPUBuffer CreateUniformBuffer(WGPUDevice device,
                                              size_t byteSize,
                                              std::string label);
    };
}

#endif