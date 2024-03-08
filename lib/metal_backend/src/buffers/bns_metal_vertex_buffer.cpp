#if USE_METAL

#include "buffers/bns_metal_vertex_buffer.hpp"
#include "bns_metal_util.hpp"
#include "renderer/bns_metal_renderer.hpp"

namespace bns
{
    MetalVertexBuffer::MetalVertexBuffer(Renderer *renderer, std::string label)
    {
        m_renderer = static_cast<MetalRenderer *>(renderer);
    }

    void MetalVertexBuffer::Initialize(size_t byteSize)
    {
        m_byteSize = byteSize;
        m_isWritable = true;
        m_buffer = MetalUtil::Buffer.CreateVertexBuffer(m_renderer->GetDevice(), byteSize);
    }

    void MetalVertexBuffer::Initialize(std::vector<f32> &data, bool isWritable)
    {
        m_byteSize = data.size() * sizeof(f32);
        m_isWritable = isWritable;
        m_buffer = MetalUtil::Buffer.CreateVertexBuffer(m_renderer->GetDevice(), data);
    }

    void MetalVertexBuffer::Update(std::vector<f32> &data, u32 offset, i32 byteSize)
    {
        size_t byteLength = byteSize < 0 ? data.size() * sizeof(f32) : static_cast<size_t>(byteSize);

        if (byteLength > m_byteSize)
        {
            std::string msg = "MetalVertexBuffer::Update: The byte length is greater than the byte size of the buffer.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        size_t byteOffset = static_cast<size_t>(offset);
        MetalUtil::Buffer.Write(m_buffer, byteLength, data, byteOffset);
    }

} // namespace bns

#endif