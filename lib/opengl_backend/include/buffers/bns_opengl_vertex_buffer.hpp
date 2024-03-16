#if USE_OPENGL

#ifndef BNS_OPENGL_VERTEX_BUFFER_HPP

#define BNS_OPENGL_VERTEX_BUFFER_HPP

#include "buffers/bns_vertex_buffer.hpp"
#include "bns_opengl.hpp"

namespace bns
{
    /// @brief The OpenGL vertex buffer.
    class OpenGLVertexBuffer : public VertexBuffer
    {
    private:
        GLuint m_buffer;

    public:
        /// @brief The constructor for the OpenGLVertexBuffer.
        /// @param label The label of the buffer.
        OpenGLVertexBuffer(std::string label = "");

        /// @brief Gets the buffer.
        /// @return The buffer.
        GLuint GetBuffer() { return m_buffer; }

        void Initialize(size_t byteSize) override;

        void Initialize(std::vector<f32> &data, bool isWritable = false) override;

        void Update(std::vector<f32> &data, u32 offset = 0, i32 byteSize = -1) override;
    };
}

#endif

#endif