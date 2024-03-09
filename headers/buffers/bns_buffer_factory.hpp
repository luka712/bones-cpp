#ifndef BNS_BUFFER_FACTORY

#define BNS_BUFFER_FACTORY

#include "buffers/bns_index_buffer.hpp"

namespace bns 
{
    /// @brief The buffer factory.
    class BufferFactory
    {
    public:
        /// @brief Creates a new instance of index buffer.
        /// @param data The data to be copied to the buffer.
        /// @param label The label of the buffer.
        /// @return The index buffer.
        IndexBuffer *CreateIndexBuffer(std::vector<u16> data, std::string label = "") ;
    };
}

#endif 