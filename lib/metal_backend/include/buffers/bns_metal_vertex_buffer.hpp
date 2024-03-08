#if USE_METAL

#ifndef BNS_METAL_VERTEX_BUFFER_HPP

#define BNS_METAL_VERTEX_BUFFER_HPP

#include "bns_metal.hpp"
#include "buffers/bns_vertex_buffer.hpp"
#include "renderer/bns_renderer.hpp"

namespace bns
{
    class MetalRenderer;

    class MetalVertexBuffer : public VertexBuffer
    {
    private:
        MetalRenderer* m_renderer;
        MTL::Buffer* m_buffer;

    public:
        /// @brief The constructor for the Metal vertex buffer.
        /// @param renderer The Metal renderer.
        /// @param label The label for the buffer.
        MetalVertexBuffer(Renderer* renderer, std::string label = "");

        /// @brief Get the Metal buffer.
        inline MTL::Buffer* GetBuffer() const { return m_buffer; }

        /// @brief Initialize the vertex buffer. This will create a writable buffer since data is not passed in.
        /// @param byteSize The size of the buffer in bytes.
        void Initialize(size_t byteSize) override;

        /// @brief Initialize the vertex buffer. This will create a read only buffer unless isWritable is set to true.
        /// @param data The data to be copied to the buffer.
        /// @param isWritable Is the buffer writable. By default false.
        /// @note Metal does not support read only buffers, so this is ignored.
        void Initialize(std::vector<f32> &data, bool isWritable = false) override;

        /// @brief Update the vertex buffer.
        /// @param data The data to be written to the buffer.
        /// @param offset The offset to write data. By default 0. This is in bytes of the buffer.
        /// @param byteSize The byte size of data. By default -1 which means the size of the data.
        void Update(std::vector<f32> &data, u32 offset = 0, i32 byteSize = -1) override;
    };

} // namespace bns

#endif

#endif // USE_METAL