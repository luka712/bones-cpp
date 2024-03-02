#if USE_WEBGPU

#ifndef BNS_WEBGPU_VERTEX_BUFFER_HPP
#define BNS_WEBGPU_VERTEX_BUFFER_HPP

#include "buffers/bns_vertex_buffer.hpp"
#include "renderer/bns_webgpu_renderer.hpp"
#include "bns_webgpu_util.hpp"

namespace bns
{
    template <typename T>
    class WebGPUVertexBuffer : public VertexBuffer<T>
    {
    private:
        WebGPURenderer *m_renderer;
        std::string m_label;
        size_t m_byteSize;

        // The buffer
        WGPUBuffer m_buffer;

    public:
        /// @brief The constructor for the WebGPUVertexBuffer.
        /// @param renderer The renderer.
        /// @param byteSize The byte size of the buffer.
        /// @param label The label of the buffer.
        WebGPUVertexBuffer(Renderer *renderer, size_t byteSize, std::string label = "")
            : m_renderer(static_cast<WebGPURenderer *>(renderer)), m_byteSize(byteSize), m_label(label)

        {
        }

        /// @brief Gets the buffer.
        inline WGPUBuffer GetBuffer() const { return m_buffer; }

        /// @brief Gets the byte size of the buffer.
        inline size_t GetByteSize() const { return m_byteSize; }

        void Initialize() override
        {
            WGPUDevice device = m_renderer->GetDevice();

            m_buffer = WebGPUUtil::Buffer.CreateVertexBuffer(device, m_byteSize, m_label.c_str());
        }
        void Update(std::vector<T> &data, u32 offset = 0, i32 byteSize = -1) override
        {
            // If byte size is less then 0, then the byte size is the size of the data. Otherwise, it is the byte size.
            size_t byteLength = byteSize < 0 ? data.size() * sizeof(T) : static_cast<size_t>(byteSize);

            if (byteLength > m_byteSize)
            {
                std::string msg = "WebGPUVertexBuffer::Update: The byte length is greater than the byte size of the buffer.";
                LOG(msg);
                BREAKPOINT();
                throw std::runtime_error(msg.c_str());
            }

            size_t byteOffset = static_cast<size_t>(offset);
            WebGPUUtil::Buffer.Write(m_renderer->GetQueue(), m_buffer, byteLength, data, byteOffset);
        }
    };
}

#endif

#endif