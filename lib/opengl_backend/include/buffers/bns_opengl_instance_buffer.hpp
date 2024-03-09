#if USE_OPENGL

#ifndef BNS_OPENGL_INSTANCE_BUFFER
#define BNS_OPENGL_INSTANCE_BUFFER

#include "buffers/bns_instance_buffer.hpp"
#include "bns_opengl_util.hpp"

namespace bns
{
    /// @brief The OpenGL instance buffer.
    template <typename T>
    class OpenGLInstanceBuffer : public InstanceBuffer<T>
    {
    private:
        GLuint m_buffer = 0;

    public:
        /// @brief The constructor for the OpenGL instance buffer.
        /// @param instanceCount The number of instances. By default, it is 1.
        /// @param label The label of the buffer.
        OpenGLInstanceBuffer(i32 instanceCount = 1, std::string label = "")
            : InstanceBuffer<T>(label)
        {
        }

        /// @brief Initializes the buffer.
        /// @param data The data to be copied to the buffer.
        /// @param isWritable Whether the buffer is writable.
        void Initialize(std::vector<T> &data, bool isWritable = false) override
        {
            GLenum hint = isWritable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
            m_buffer = OpenGLUtil::Buffer.CreateVertexBuffer<T>(data, hint, m_label);
        }

        /// @brief Update the constant buffer.
        virtual void Update(std::vector<T> &data, i32 instance = 1) 
        {
            // TODO:
            BREAKPOINT();
        }

        /// @brief Dispose the constant buffer.
        void Dispose() override
        {
            OpenGLUtil::Buffer.Dispose(m_buffer);
        }
    };
}

#endif

#endif