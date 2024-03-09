#if USE_OPENGL

#include "buffers/bns_opengl_index_buffer.hpp"
#include "bns_opengl_util.hpp"

namespace bns 
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(std::string label)
    : IndexBuffer(label)
    {
    }

    void OpenGLIndexBuffer::Initialize(std::vector<u16> &data)
    {
        m_buffer = OpenGLUtil::Buffer.CreateIndexBuffer(data, m_label);
    }

    void OpenGLIndexBuffer::Dispose()
    {
        glDeleteBuffers(1, &m_buffer);
    }
}

#endif 