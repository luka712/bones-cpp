#if USE_OPENGL

#ifndef BNS_OPENGL_INDEX_BUFFER_HPP

#define BNS_OPENGL_INDEX_BUFFER_HPP

#include "buffers/bns_index_buffer.hpp"
#include "bns_opengl.hpp"

namespace bns
{
    /// @brief The OpenGL index buffer.
    class OpenGLIndexBuffer : public IndexBuffer
    {
    private:
        u32 m_buffer;

    public:
        /// @brief The constructor for the OpenGL index buffer.
        /// @param label The label of the buffer.
        OpenGLIndexBuffer(std::string label = "");

        /// @brief Get the buffer.
        u32 GetBuffer() const{ return m_buffer; }

        /// @brief Initialize the index buffer.
        /// @param data The data to be copied to the buffer.
        void Initialize(std::vector<u16> &data) override;

        /// @brief Dispose the index buffer.
        void Dispose() override;
    };
}

#endif 

#endif 