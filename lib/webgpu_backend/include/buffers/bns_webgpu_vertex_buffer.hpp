#if USE_WEBGPU

#ifndef BNS_WEBGPU_VERTEX_BUFFER_HPP
#define BNS_WEBGPU_VERTEX_BUFFER_HPP

#include "buffers/bns_vertex_buffer.hpp"
#include "renderer/bns_webgpu_renderer.hpp"
#include "bns_webgpu_util.hpp"

namespace bns
{
    class WebGPUVertexBuffer : public VertexBuffer
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
        WebGPUVertexBuffer(Renderer *renderer, std::string label = "");

        /// @brief Gets the buffer.
        inline WGPUBuffer GetBuffer() const { return m_buffer; }

        void Initialize(size_t byteSize) override;
        void Initialize(std::vector<f32> &data, bool isWritable = false) override;
        void Update(std::vector<f32> &data, u32 offset = 0, i32 byteSize = -1) override;
    };
}

#endif

#endif