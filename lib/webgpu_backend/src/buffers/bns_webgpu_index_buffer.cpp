#if USE_WEBGPU

#include "buffers/bns_webgpu_index_buffer.hpp"
#include "bns_webgpu_util.hpp"

namespace bns 
{
    WebGPUIndexBuffer::WebGPUIndexBuffer(Renderer *renderer, std::string label)
    {
        m_renderer = static_cast<WebGPURenderer *>(renderer);
        m_label = label;
    }

    void WebGPUIndexBuffer::Initialize(std::vector<u16> &data)
    {
        m_byteSize = data.size() * sizeof(u16);
        m_indicesCount = data.size();
        m_buffer = WebGPUUtil::Buffer.CreateIndexBuffer(m_renderer->GetDevice(), data, m_label);
    }
}

#endif 