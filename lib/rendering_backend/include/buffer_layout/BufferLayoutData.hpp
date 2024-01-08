#ifndef BNS_BUFFER_LAYOUT_DATA_HPP

#define BNS_BUFFER_LAYOUT_DATA_HPP

#include "Types.hpp"
#include <vector>
#include "RenderingBackendTypes.hpp"

/**
 * The data that will be used for the buffer layout classes
 */

namespace bns
{
    /// @brief The buffer layout descriptor.    
    struct BufferLayoutAttributeDescriptor
    {
        BufferLayoutAttributeDescriptor(VertexFormat format);

        BufferLayoutAttributeDescriptor(VertexFormat format, size_t shaderLocation, size_t offset);

        /// @brief  The format of the buffer layout.
        VertexFormat Format;

        /// @brief The shader location.
        size_t ShaderLocation;

        /// @brief The offset compared to previous attribute.
        size_t Offset;
    };

    struct BufferLayoutDescriptor
    {
        BufferLayoutDescriptor();

        std::vector<BufferLayoutAttributeDescriptor> Attributes;

        /// @brief The size of the buffer layout. Describes the size of single vertex.
        size_t Stride;

        /// @brief The step mode of the buffer layout.
        VertexStepMode Step;

        /// @brief The byte size of the buffer. The total buffer size.
        size_t ByteSize;

        /// @brief The pointer to the data.
        void *Data;
    };
}

#endif // !BNS_BUFFER_LAYOUT_DATA_HPP