#if USE_METAL

#include "util/bns_metal_buffer_util.hpp"

namespace bns
{
    MTL::Buffer *MetalBufferUtil::Create(MTL::Device *device, size_t byteSize, std::string label)
    {
        MTL::Buffer *buffer = device->newBuffer(byteSize, MTL::ResourceCPUCacheModeDefaultCache);
        NS::String *nsLabel = NS::String::string(label.c_str(), NS::StringEncoding::UTF8StringEncoding);
        buffer->setLabel(nsLabel);
        nsLabel->release();

        return buffer;
    }

    MTL::Buffer *MetalBufferUtil::CreateVertexBuffer(MTL::Device *device, std::vector<f32> &data, std::string label)
    {
        // No difference, metal just has buffer. Just create one with u16 data.
        return Create(device, data, label);
    }

    MTL::Buffer *MetalBufferUtil::CreateIndexBuffer(MTL::Device *device, std::vector<u16> &data, std::string label)
    {
        // No difference, metal just has buffer. Just create one with u16 data.
        return Create(device, data, label);
    }

    MTL::Buffer *MetalBufferUtil::CreateVertexBuffer(MTL::Device *device, size_t byteSize, std::string label)
    {
        return Create(device, byteSize, label);
    }

    void MetalBufferUtil::Dispose(MTL::Buffer *buffer)
    {
        buffer->release();
    }
}

#endif
