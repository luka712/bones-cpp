#if USE_OPENGL

#ifndef BNS_OPENGL_UNIFORM_BUFFER_HPP

#define BNS_OPENGL_UNIFORM_BUFFER_HPP

#include "buffers/bns_uniform_buffer.hpp"
#include "renderer/bns_opengl_renderer.hpp"
#include <string>
#include "bns_opengl_util.hpp"

namespace bns
{
    /// @brief The webgpu uniform buffer.
    template <typename T>
    class OpenGLUniformBuffer : public UniformBuffer<T>
    {
    private:
        GLuint m_bufferId;
        std::string m_label;

    public:
        /// @brief The constructor for the constant buffer.
        /// @param renderer The renderer.
        /// @param label The label of the buffer. By default, it is empty.
        OpenGLUniformBuffer(std::string label = "")
        {
            m_label = label;
        }

        /// @brief Destructor for the constant buffer.
        ~OpenGLUniformBuffer()
        {
            Dispose();
        }

        /// @brief Get the buffer.
        /// @return The buffer.
        GLuint GetBuffer() const { return m_bufferId; }

        void Initialize() override
        {
            m_bufferId = OpenGLUtil::Buffer.CreateUniformBuffer(sizeof(T), m_label, GL_DYNAMIC_DRAW);
        }

        void Update(T &data) override
        {
            OpenGLUtil::Buffer.WriteUniformBuffer(m_bufferId, &data);
        }

        void Dispose() override
        {
            OpenGLUtil::Buffer.Dispose(m_bufferId);
            m_bufferId = 0;
        }
    };
}

#endif

#endif