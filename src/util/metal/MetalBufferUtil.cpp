#include "util/metal/MetalBufferUtil.hpp"

namespace bns
{
    MTL::Buffer *MetalBufferUtil::CreateVertexBuffer(MTL::Device *device, std::vector<f32> data, std::string label)
    {
        size_t byteSize = data.size() * sizeof(f32);

        MTL::Buffer *buffer = device->newBuffer(data.data(), byteSize, MTL::ResourceOptionCPUCacheModeDefault);
        NS::String *nsLabel = NS::String::string(label.c_str(), NS::StringEncoding::UTF8StringEncoding);
        buffer->setLabel(nsLabel);
        nsLabel->release();

        return buffer;
    }
}