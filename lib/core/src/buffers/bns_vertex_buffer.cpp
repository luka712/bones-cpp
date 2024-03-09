#include "buffers/bns_vertex_buffer.hpp"

namespace bns
{
    VertexBuffer::VertexBuffer(std::string label)
        :  m_label(label), m_isWritable(true), m_byteSize(0)
    {
    }
}