#if USE_METAL

#ifndef BNS_METAL_VERTEX_BUFFER_LAYOUT_UTIL_HPP

#define BNS_METAL_VERTEX_BUFFER_LAYOUT_UTIL_HPP

#include "bns_metal.hpp"
#include <vector>
#include <map>
#include "buffer_layout/BufferLayoutData.hpp"

namespace bns
{
    /**
     * Simple class which serves as placeholder for the vertex buffer layouts and their attributes.
    */
    struct MetalVertexBufferLayoutAttributesDto final
    {
        std::vector<MTL::VertexBufferLayoutDescriptor *> BufferLayouts;
        std::vector<MTL::VertexAttributeDescriptor *> BufferAttributes;
    };

    class MetalVertexBufferLayoutUtil final
    {
    private:
        inline static std::map<VertexFormat, MTL::VertexFormat> m_vertexFormatMap = {
            {VertexFormat::Float32x2, MTL::VertexFormatFloat2},
            {VertexFormat::Float32x3, MTL::VertexFormatFloat3},
            {VertexFormat::Float32x4, MTL::VertexFormatFloat4}};

        inline static std::map<VertexStepMode, MTL::VertexStepFunction> m_vertexStepModeMap = {
            {VertexStepMode::Vertex, MTL::VertexStepFunctionPerVertex}};

    public:
        /**
         * @brief Create a vertex buffer layout.
         * @return The vertex buffer layout.
         */
        static MetalVertexBufferLayoutAttributesDto Create(std::vector<BufferLayoutDescriptor> &descriptors);

        /**
         * @brief Delete the vertex buffer layouts and their attributes.
         * @param bufferLayouts The vertex buffer layouts.
         */
        static void DeleteVertexBufferLayouts(MetalVertexBufferLayoutAttributesDto dto);
    };
}

#endif // !BNS_METAL_VERTEX_BUFFER_LAYOUT_UTIL_HPP

#endif // __APPLE__
