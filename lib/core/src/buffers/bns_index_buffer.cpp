#include "buffers/bns_index_buffer.hpp"

namespace bns
{
    IndexBuffer::IndexBuffer(std::string label)
        : m_indicesCount(0), m_byteSize(0), m_label(label)
    {
    }
}