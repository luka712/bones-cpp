#if USE_METAL

#ifndef BNS_METAL_INDEX_BUFFER_HPP

#define BNS_METAL_INDEX_BUFFER_HPP

#include "buffers/bns_index_buffer.hpp"
#include "renderer/bns_metal_renderer.hpp"

namespace bns
{
    /// @brief The Metal index buffer.
    class MetalIndexBuffer : public IndexBuffer
    {
    private:
        MetalRenderer *m_renderer;
        std::string m_label;

        // The buffer
        MTL::Buffer *m_buffer;

    public:
        /// @brief The constructor for the MetalVertexBuffer.
        /// @param renderer The renderer.
        /// @param label The label of the buffer.
        MetalIndexBuffer(Renderer *renderer, std::string label = "");

        /// @brief Gets the buffer.
        inline MTL::Buffer *GetBuffer() const { return m_buffer; }

        void Initialize(std::vector<u16> &data) override;

        /// @brief Dispose the index buffer.
        void Dispose() override;
    };
}

#endif

#endif