#if USE_METAL

#include "util/MetalVertexBufferLayoutUtil.hpp"

namespace bns
{
    MetalVertexBufferLayoutAttributesDto MetalVertexBufferLayoutUtil::Create(std::vector<BufferLayoutDescriptor> &descriptors)
    {
        MetalVertexBufferLayoutAttributesDto dto;

        for (size_t i = 0; i < descriptors.size(); i++)
        {
            auto desc = descriptors[i];

            MTL::VertexBufferLayoutDescriptor *bufferLayout = MTL::VertexBufferLayoutDescriptor::alloc();
            bufferLayout->setStride(NS::UInteger(desc.Stride));
            bufferLayout->setStepFunction(m_vertexStepModeMap[desc.Step]);
            bufferLayout->setStepRate(NS::UInteger(1));

            for (size_t j = 0; j < desc.Attributes.size(); j++)
            {
                auto attr = desc.Attributes[j];

                MTL::VertexAttributeDescriptor *attrDescriptor = MTL::VertexAttributeDescriptor::alloc();
                attrDescriptor->setFormat(m_vertexFormatMap[attr.Format]);
                attrDescriptor->setOffset(NS::UInteger(attr.Offset));
                attrDescriptor->setBufferIndex(NS::UInteger(i)); // the buffer index

                dto.BufferAttributes.push_back(attrDescriptor);
            }

            dto.BufferLayouts.push_back(bufferLayout);
        }
        return dto;
    }

    void MetalVertexBufferLayoutUtil::DeleteVertexBufferLayouts(MetalVertexBufferLayoutAttributesDto dto)
    {
        for (size_t i = 0; i < dto.BufferLayouts.size(); i++)
        {
            dto.BufferLayouts[i]->release();
        }

        for (size_t i = 0; i < dto.BufferAttributes.size(); i++)
        {
            dto.BufferAttributes[i]->release();
        }
    }
}

#endif // __APPLE__