#ifndef BNS_BUFFER_LAYOUT_DATA_HPP

#define BNS_BUFFER_LAYOUT_DATA_HPP

#include "Types.hpp"
#include <vector>

/**
 * The data that will be used for the buffer layout classes
 */

namespace bns
{
    enum class StepMode
    {
        Vertex
    };

    enum class VertexFormat
    {
        Float32x2,
        Float32x3,
        Float32x4
    };

    /**
     * The buffer layout descriptor.
     */
    struct BufferLayoutAttributeDescriptor
    {
        BufferLayoutAttributeDescriptor(VertexFormat format);

        BufferLayoutAttributeDescriptor(VertexFormat format, size_t shaderLocation, size_t offset);

        /**
         * The format of the buffer layout.
         */
        VertexFormat Format;

        /**
         * The shader location.
         */
        size_t ShaderLocation;

        /**
         * The offset compared to previous attribute.
         */
        size_t Offset;
    };

    struct BufferLayoutDescriptor
    {
        BufferLayoutDescriptor();

        std::vector<BufferLayoutAttributeDescriptor> Attributes;

        /**
         * The offset compared to previous attribute.
         */
        size_t Stride;

        /**
         * The step mode of the buffer layout.
         */
        StepMode Step;
    };
}

#endif // !BNS_BUFFER_LAYOUT_DATA_HPP 