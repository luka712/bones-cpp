#if USE_OPENGL

#include "buffers/bns_opengl_vertex_buffer.hpp"
#include "bns_opengl_util.hpp"

namespace bns
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(std::string label)
        : VertexBuffer(label)
    {
    }

    void OpenGLVertexBuffer::Initialize(size_t byteSize)
    {
        m_buffer = OpenGLUtil::Buffer.CreateVertexBuffer(byteSize, GL_DYNAMIC_DRAW, m_label);
        m_isWritable = true;
    }

    void OpenGLVertexBuffer::Initialize(std::vector<f32> &data, bool isWritable)
    {
        GLenum hint = isWritable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
        m_buffer = OpenGLUtil::Buffer.CreateVertexBuffer(data, hint, m_label);
        m_isWritable = isWritable;
    }

    void OpenGLVertexBuffer::Update(std::vector<f32> &data, u32 offset, i32 byteSize)
    {
       OpenGLUtil::Buffer.WriteVertexBuffer(m_buffer, byteSize, data, offset);
    }
}

#endif