#if USE_METAL

#ifndef BNS_METAL_BUFFER_UTIL_HPP

#define BNS_METAL_BUFFER_UTIL_HPP

#include "bns_metal.hpp"
#include "bns_types.hpp"
#include "bns_rendering_backend_types.hpp"
#include <vector>
#include <string>
#include <stdexcept>

namespace bns
{
    // Note: In Metal there is no difference between vertex and index buffers. They are just buffers.
    // However, the data written to them is different. Also for consistency with other backends, the methods are named CreateVertexBuffer and CreateIndexBuffer.

    /// @brief The Metal buffer utility class.
    struct MetalBufferUtil
    {
        /// @brief Creates buffer and writes data to it.
        /// @param device The Metal device.
        /// @param data The data to be written to the buffer.
        /// @param label The label for the buffer.
        /// @return The Metal buffer. This buffer is in private mode.
        template <typename T>
        static MTL::Buffer *Create(MTL::Device *device,
                                   std::vector<T> &data,
                                   std::string label = "")
        {
            size_t byteSize = data.size() * sizeof(T);

            MTL::Buffer *buffer = device->newBuffer(data.data(), byteSize, MTL::ResourceOptionCPUCacheModeDefault);
            NS::String *nsLabel = NS::String::string(label.c_str(), NS::StringEncoding::UTF8StringEncoding);
            buffer->setLabel(nsLabel);
            nsLabel->release();

            return buffer;
        }

        /// @brief Creates buffer and writes data to it.
        /// @param device The Metal device.
        /// @param data The data to be written to the buffer.
        /// @param label The label for the buffer.
        /// @return The Metal buffer. This buffer is in private mode.
        template <typename T>
        static MTL::Buffer *CreateWithGPUOnlyAccess(
                                   MTL::BlitCommandEncoder *blitCommandEncoder,
                                   MTL::Device *device,
                                   std::vector<T> &data,
                                   std::string label = "")
        {
            size_t byteSize = data.size() * sizeof(T);

            // https://developer.apple.com/documentation/metal/resource_fundamentals/choosing_a_resource_storage_mode_for_apple_gpus?language=objc
            MTL::Buffer *tempBuffer = device->newBuffer(data.data(), byteSize, MTL::ResourceOptionCPUCacheModeDefault); // Created by default as MTLResourceStorageModeShared

            // Create buffer that can be only accessed by GPU
            MTL::Buffer *buffer = device->newBuffer(byteSize, MTL::ResourceOptionCPUCacheModeDefault | MTL::ResourceStorageModePrivate);
            NS::String *nsLabel = NS::String::string(label.c_str(), NS::StringEncoding::UTF8StringEncoding);
            buffer->setLabel(nsLabel);
            nsLabel->release();

            // Copy data from tempBuffer to buffer
            blitCommandEncoder->copyFromBuffer(tempBuffer, 0, buffer, 0, byteSize);

            tempBuffer->release();

            return buffer;
        }


        /// @brief Creates buffer with a given size and no data written to it.
        /// @param device The Metal device.
        /// @param byteSize The size of the buffer in bytes.
        /// @param label The label for the buffer.
        /// @return The Metal buffer.
        static MTL::Buffer *Create(MTL::Device *device, size_t byteSize, std::string label = "");

        /// @brief Creates vertex buffer and writes data to it. It has no difference to Create method.
        /// @param device The Metal device.
        /// @param data The data to be written to the buffer.
        /// @param label The label for the buffer.
        /// @return The Metal buffer. This buffer is in private mode.
        static MTL::Buffer *CreateVertexBuffer(MTL::Device *device, std::vector<f32> &data, std::string label = "");

        /// @brief Creates vertex buffer with a given size and no data written to it. It has no difference to Create method.
        /// @param device The Metal device.
        /// @param byteSize The size of the buffer in bytes.
        /// @param label The label for the buffer.
        /// @return The Metal buffer.
        static MTL::Buffer *CreateVertexBuffer(MTL::Device *device, size_t byteSize, std::string label = "");

        /// @brief Creates index buffer and writes data to it. With metal there is no difference between buffers, just different data is written to them.
        /// @param device The Metal device.
        /// @param data The data to be written to the buffer.
        /// @param label The label for the buffer.
        /// @return The Metal buffer.
        static MTL::Buffer *CreateIndexBuffer(MTL::Device *device, std::vector<u16> &data, std::string label = "");

        /// @brief Writes data to the buffer.
        /// @param buffer The Metal buffer.
        /// @param byteSize The size of the data in bytes.
        /// @param data The data to be written to the buffer.
        /// @param byteOffset The offset to write data. By default 0. This is in bytes of the buffer.
        template <typename T>
        static void Write(MTL::Buffer *buffer, size_t byteSize, std::vector<T> &data, size_t byteOffset = 0)
        {
            if (byteSize > buffer->length())
            {
                std::string msg = "MetalBufferUtil::Write: The byte length is greater than the byte size of the buffer.";
                LOG(msg);
                BREAKPOINT();
                throw std::runtime_error(msg.c_str());
            }

            char *gpuMemoryPtr = static_cast<char *>(buffer->contents());
            char *gpuOffsetMemoryPtr = &gpuMemoryPtr[byteOffset];
            std::memcpy(gpuOffsetMemoryPtr, data.data(), byteSize);
        }

        /// @brief Disposes the buffer.
        /// @param buffer The Metal buffer.
        static void Dispose(MTL::Buffer *buffer);
    };
}

#endif

#endif
