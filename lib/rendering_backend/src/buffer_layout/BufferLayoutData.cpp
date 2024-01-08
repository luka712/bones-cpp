#include "buffer_layout/BufferLayoutData.hpp"

namespace bns
{
    BufferLayoutAttributeDescriptor::BufferLayoutAttributeDescriptor(VertexFormat format)
        : Format(format)
    {
        Offset = 0;
        ShaderLocation = 0;
    }

    BufferLayoutAttributeDescriptor::BufferLayoutAttributeDescriptor(VertexFormat format, size_t shaderLocation, size_t offset)
        : Format(format), ShaderLocation(shaderLocation), Offset(offset)
    {
    }

    BufferLayoutDescriptor::BufferLayoutDescriptor()
    {
        Step = VertexStepMode::Vertex;
        Stride = 0;
        ByteSize = 0;
        Data = nullptr;
    }
}