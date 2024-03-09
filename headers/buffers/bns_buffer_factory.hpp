#ifndef BNS_BUFFER_FACTORY

#define BNS_BUFFER_FACTORY

#include "buffers/bns_index_buffer.hpp"
#include "buffers/bns_vertex_buffer.hpp"

namespace bns
{
    class Framework;

    /// @brief The buffer factory.
    class BufferFactory
    {
    private:
        Framework *m_framework;

    public:
        /// @brief The constructor for the buffer factory.
        /// @param framework The framework.
        BufferFactory(Framework *framework);

        /// @brief Creates a new instance of index buffer.
        /// @param data The data to be copied to the buffer.
        /// @param label The label of the buffer.
        /// @return The index buffer.
        IndexBuffer *CreateIndexBuffer(std::vector<u16> data, std::string label = "");

        /// @brief Creates a new instance of vertex buffer.
        /// @param data The data to be copied to the buffer.
        /// @param label The label of the buffer.
        /// @return The vertex buffer.
        VertexBuffer *CreateVertexBuffer(std::vector<f32> data, std::string label = "");
    };
}

#endif