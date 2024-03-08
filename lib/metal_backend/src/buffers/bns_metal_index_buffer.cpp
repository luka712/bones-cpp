#if USE_METAL

#include "buffers/bns_metal_index_buffer.hpp"
#include "bns_metal_util.hpp"

namespace bns 
{
    MetalIndexBuffer::MetalIndexBuffer(Renderer *renderer, std::string label)
    {
        m_renderer = static_cast<MetalRenderer *>(renderer);
        m_label = label;
    }

    void MetalIndexBuffer::Initialize(std::vector<u16> &data)
    {
        m_buffer = MetalUtil::Buffer.CreateIndexBuffer(m_renderer->GetDevice(), data, m_label);
        m_indicesCount = data.size();
    }
}

#endif 
