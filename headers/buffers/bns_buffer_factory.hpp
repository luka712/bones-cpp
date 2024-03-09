#ifndef BNS_BUFFER_FACTORY

#define BNS_BUFFER_FACTORY

#include "buffers/bns_index_buffer.hpp"
#include "buffers/bns_vertex_buffer.hpp"

#if USE_WEBGPU
#include "buffers/bns_webgpu_instance_buffer.hpp"
#endif

#if USE_OPENGL
#include "buffers/bns_opengl_instance_buffer.hpp"
#endif
namespace bns
{
    class Framework;

    /// @brief The buffer factory.
    class BufferFactory
    {
    private:
        Framework *m_framework;

    public:
        /// @brief The constructor for the buffer factory.
        /// @param framework The framework.
        BufferFactory(Framework *framework);

        /// @brief Creates a new instance of index buffer.
        /// @param data The data to be copied to the buffer.
        /// @param label The label of the buffer.
        /// @return The index buffer.
        IndexBuffer *CreateIndexBuffer(std::vector<u16> &data, std::string label = "");

        /// @brief Creates a new instance of vertex buffer.
        /// @param data The data to be copied to the buffer.
        /// @param label The label of the buffer.
        /// @return The vertex buffer.
        VertexBuffer *CreateVertexBuffer(std::vector<f32> &data, std::string label = "");

        /// @brief Creates a new instance of instance buffer.
        /// @param data The data to be copied to the buffer.
        /// @param numberOfInstances The number of instances. By default, it is 1.
        /// @param isWritable Whether the buffer is writable. By default, it is true.
        /// @param label The label of the buffer. By default, it is an empty string.
        /// @return The instance buffer.
        template <typename T>
        InstanceBuffer<T> *CreateInstanceBuffer(std::vector<T> &data, i32 numberOfInstances = 1, bool isWritable = true, std::string label = "")
        {
            InstanceBuffer<T> *instanceBuffer = nullptr;

#if USE_WEBGPU
            if (m_framework->GetRendererType() == RendererType::WebGPU)
            {
                instanceBuffer = new WebGPUInstanceBuffer<T>(m_framework->GetRenderer(), numberOfInstances, label);
            }
#endif

#if USE_OPENGL
            if (m_framework->GetRendererType() == RendererType::OpenGL)
            {
                instanceBuffer = new OpenGLInstanceBuffer<T>(numberOfInstances,label);
            }
#endif

            instanceBuffer->Initialize(data, isWritable);
            return instanceBuffer;
        }
    };
}

#endif