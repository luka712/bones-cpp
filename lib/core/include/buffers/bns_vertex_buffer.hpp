#ifndef BNS_VERTEX_BUFFER_HPP

#define BNS_VERTEX_BUFFER_HPP

#include "bns_types.hpp"
#include <vector>

namespace bns
{
    template <typename T>
    class VertexBuffer
    {
    public:
        /// @brief Initialize the vertex buffer.
        virtual void Initialize() = 0;

        /// @brief Update the vertex buffer.
        /// @param data The data to be written to the buffer.
        /// @param offset The offset to write data. By default 0. This is in bytes of the buffer.
        /// @param byteSize The byte size of data. By default -1 which means the size of the data.
        virtual void Update(std::vector<T>& data, u32 offset = 0, i32 byteSize = -1) = 0;
    };
}

#endif 