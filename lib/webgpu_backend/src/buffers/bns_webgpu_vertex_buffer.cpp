#if USE_WEBGPU

#include "buffers/bns_webgpu_vertex_buffer.hpp"
#include "bns_webgpu_util.hpp"

namespace bns
{
    WebGPUVertexBuffer::WebGPUVertexBuffer(Renderer *renderer, std::string label)
        : m_renderer(static_cast<WebGPURenderer *>(renderer)), m_label(label)
    {
    }

    void WebGPUVertexBuffer::Initialize(size_t byteSize)
    {
        m_isWritable = true;
        m_byteSize = byteSize;
        m_buffer = WebGPUUtil::Buffer.CreateVertexBuffer(m_renderer->GetDevice(), byteSize, m_label);
    }

    void WebGPUVertexBuffer::Initialize(std::vector<f32> &data, bool isWritable)
    {
        m_isWritable = isWritable;
        m_byteSize = data.size() * sizeof(float);

        // Setup buffer usage, by default vertex. Not really necessary since it's set in the CreateVertexBuffer method, but leave it for clarity.
        WGPUBufferUsageFlags usage = WGPUBufferUsage_Vertex;
        if(isWritable)
        {
            usage = usage | WGPUBufferUsage_CopyDst;
        }

        m_buffer = WebGPUUtil::Buffer.CreateVertexBuffer(m_renderer->GetDevice(), data, m_label, usage);
    }

    void WebGPUVertexBuffer::Update(std::vector<f32> &data, u32 offset, i32 byteSize)
    {
        // If byte size is less then 0, then the byte size is the size of the data. Otherwise, it is the byte size.
        size_t byteLength = byteSize < 0 ? data.size() * sizeof(float) : static_cast<size_t>(byteSize);

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
}

#endif