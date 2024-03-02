#ifndef BNS_VERTEX_BUFFER_HPP

#define BNS_VERTEX_BUFFER_HPP

#include "bns_types.hpp"
#include <vector>

namespace bns
{
    class VertexBuffer
    {
    protected:
        /// @brief Is buffer writable.
        bool m_isWritable;

    public:
        /// @brief Initialize the vertex buffer. This will create a writable buffer since data is not passed in.
        /// @param byteSize The size of the buffer in bytes.
        virtual void Initialize(size_t byteSize) = 0;

        /// @brief Initialize the vertex buffer. This will create a read only buffer unless isWritable is set to true.
        /// @param data The data to be copied to the buffer.
        /// @param isWritable Is the buffer writable. By default false.
        virtual void Initialize(std::vector<f32> &data, bool isWritable = false) = 0;

        /// @brief Update the vertex buffer.
        /// @param data The data to be written to the buffer.
        /// @param offset The offset to write data. By default 0. This is in bytes of the buffer.
        /// @param byteSize The byte size of data. By default -1 which means the size of the data.
        virtual void Update(std::vector<f32> &data, u32 offset = 0, i32 byteSize = -1) = 0;
    };
}

#endif