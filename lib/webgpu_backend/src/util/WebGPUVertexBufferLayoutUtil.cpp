#include "util/WebGPUVertexBufferLayoutUtil.hpp"

namespace bns
{
    WGPUVertexBufferLayout *WebGPUVertexBufferLayoutUtil::Create(std::vector<BufferLayoutDescriptor> &descriptors, size_t *outCount)
    {
        // Vertex state
        WGPUVertexBufferLayout *bufferLayouts = new WGPUVertexBufferLayout[descriptors.size()];
        *outCount = descriptors.size();

        size_t i = 0;
        for (BufferLayoutDescriptor& desc : descriptors)
        {
            // Create layout
            WGPUVertexBufferLayout bufferLayout = {};
            bufferLayout.arrayStride = desc.Stride;
            bufferLayout.stepMode = WebGPUVertexBufferLayoutUtil::m_vertexStepModeMap[desc.Step];

            // set the attribute count
            bufferLayout.attributeCount = desc.Attributes.size();

            // create attributes
            WGPUVertexAttribute *attributes = new WGPUVertexAttribute[desc.Attributes.size()];
            size_t j = 0;
            for (auto attr : desc.Attributes)
            {
                WGPUVertexAttribute attribute;
                attribute.format = WebGPUVertexBufferLayoutUtil::m_vertexFormatMap[attr.Format];
                attribute.offset = attr.Offset;
                attribute.shaderLocation = (uint32_t)attr.ShaderLocation;
                attributes[j] = attribute;
                j++;
            }

            // set attributes
            bufferLayout.attributes = &attributes[0];
            bufferLayouts[i] = bufferLayout;
            i++;
        }

        return bufferLayouts;
    }

    void WebGPUVertexBufferLayoutUtil::Delete(WGPUVertexBufferLayout *bufferLayouts, size_t count)
    {
        for (size_t i = 0; i < count; i++)
        {
            delete[] bufferLayouts[i].attributes;
        }

        delete[] bufferLayouts;
    }
}
