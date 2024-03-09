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
        u32 m_bufferId;

    public:
        /// @brief Initialize the index buffer.
        /// @param data The data to be copied to the buffer.
        void Initialize(std::vector<u16> &data) override;

        /// @brief Dispose the index buffer.
        void Dispose() override;
    };
}

#endif 

#endif 