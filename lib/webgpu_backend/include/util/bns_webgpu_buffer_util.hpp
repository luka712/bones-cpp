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
        /// @brief Create a vertex buffer.
        /// @param device The webgpu device.
        /// @param data The data to be copied to the buffer.
        /// @param label The label of the buffer.
        /// @param usage The usage of the buffer. By default WGPUBufferUsage_None.
        /// @return The vertex buffer. 
        /// @note This buffer is mapped at creation and cannot be written into unless BufferUsage is set appropriately.
        /// @note The data is copied to the buffer at creation.
        static WGPUBuffer CreateVertexBuffer(WGPUDevice device,
                                             std::vector<f32> data,
                                             std::string label,
                                             WGPUBufferUsageFlags usage = WGPUBufferUsage_None);

        /// @brief Create a vertex buffer. 
        /// Buffer usage is set to Vertex and CopyDst by default. Must by CopyDst since there is no data to write at creation.
        /// @param device The webgpu device.
        /// @param byteSize The size of the buffer in bytes.
        /// @param label The label of the buffer.
        /// @return The vertex buffer.
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

        /// @brief Create a uniform buffer
        /// @param device The webgpu device
        /// @param byteSize The size of the buffer in bytes
        /// @param label The label of the buffer
        /// @return The uniform buffer
        static WGPUBuffer CreateUniformBuffer(WGPUDevice device,
                                              size_t byteSize,
                                              std::string label);

        /// @brief Update the uniform buffer
        /// @param queue The webgpu queue.
        /// @param buffer The buffer to be updated.
        /// @param byteSize The size of the buffer in bytes.
        /// @param data The data to be copied to the buffer.
        /// @param offset The offset of the buffer in bytes. By default 0.
        static void UpdateUniformBuffer(WGPUQueue queue,
                                        WGPUBuffer buffer,
                                        size_t byteSize,
                                        void *data,
                                        size_t offset = 0);

        /// @brief Write to the buffer
        /// @param queue The webgpu queue.
        /// @param buffer The buffer to be written to.
        /// @param byteSize The size of the buffer in bytes.
        /// @param data The data to be copied to the buffer.
        /// @param offset The offset of the buffer in bytes. By default 0.
        template <typename T>
        static void Write(WGPUQueue queue, WGPUBuffer buffer, size_t byteSize, std::vector<T>& data, size_t offset = 0)
        {
            wgpuQueueWriteBuffer(queue, buffer, offset, data.data(), byteSize);
        }

        /// @brief Dispose the buffer.
        /// @param buffer The buffer to be disposed.
        static void Dispose(WGPUBuffer buffer);
    };
}

#endif