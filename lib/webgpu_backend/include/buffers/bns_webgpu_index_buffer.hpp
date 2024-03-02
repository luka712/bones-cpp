#if USE_WEBGPU

#ifndef BNS_WEBGPU_INDEX_BUFFER_HPP

#define BNS_WEBGPU_INDEX_BUFFER_HPP

#include "buffers/bns_index_buffer.hpp"
#include "renderer/bns_webgpu_renderer.hpp"

namespace bns
{
    /// @brief The webgpu index buffer.
    class WebGPUIndexBuffer : public IndexBuffer
    {
    private:
        WebGPURenderer *m_renderer;
        std::string m_label;

        // The buffer
        WGPUBuffer m_buffer;

    public:
        /// @brief The constructor for the WebGPUVertexBuffer.
        /// @param renderer The renderer.
        /// @param label The label of the buffer.
        WebGPUIndexBuffer(Renderer *renderer, std::string label = "");

        /// @brief Gets the buffer.
        inline WGPUBuffer GetBuffer() const { return m_buffer; }

        void Initialize(std::vector<u16> &data) override;
    };
}

#endif

#endif