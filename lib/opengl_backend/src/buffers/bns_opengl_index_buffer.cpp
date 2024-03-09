#if USE_OPENGL

#include "buffers/bns_opengl_index_buffer.hpp"
#include "bns_opengl_util.hpp"

namespace bns 
{
    void OpenGLIndexBuffer::Initialize(std::vector<u16> &data)
    {
        glGenBuffers(1, &m_bufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(u16), data.data(), GL_STATIC_DRAW);
    }

    void OpenGLIndexBuffer::Dispose()
    {
        glDeleteBuffers(1, &m_bufferId);
    }
}

#endif 