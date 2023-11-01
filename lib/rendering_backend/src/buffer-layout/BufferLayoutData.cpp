#include "buffer-layout/BufferLayoutData.hpp"

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
            Step = StepMode::Vertex;
            Stride = 0;
        }
}