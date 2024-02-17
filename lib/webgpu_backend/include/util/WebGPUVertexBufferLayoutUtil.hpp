#ifndef BNS_WEBGPU_VERTEX_BUFFER_LAYOUT_UTIL_HPP

#define BNS_WEBGPU_VERTEX_BUFFER_LAYOUT_UTIL_HPP

#include "bns_webgpu.hpp"
#include <vector>
#include <map>
#include "buffer_layout/BufferLayoutData.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref WGPUVertexBufferLayout structs
    class WebGPUVertexBufferLayoutUtil final
    {
    private:
        inline static std::map<VertexFormat, WGPUVertexFormat> m_vertexFormatMap = {
            {VertexFormat::Float32x2, WGPUVertexFormat::WGPUVertexFormat_Float32x2},
            {VertexFormat::Float32x3, WGPUVertexFormat::WGPUVertexFormat_Float32x3},
            {VertexFormat::Float32x4, WGPUVertexFormat::WGPUVertexFormat_Float32x4}};

        inline static std::map<VertexStepMode, WGPUVertexStepMode> m_vertexStepModeMap = {
            {VertexStepMode::Vertex, WGPUVertexStepMode::WGPUVertexStepMode_Vertex}};

    public:
        /// @brief Creates an array of @see WGPUVertexBufferLayout
        /// @param descriptors The buffer layout descriptors.
        /// @param count The number of vertex buffer layouts that are created.
        /// @return The created array of @see WGPUVertexBufferLayout
        static WGPUVertexBufferLayout* Create(std::vector<BufferLayoutDescriptor> &descriptors, size_t *outCount);

        /**
         * @brief Delete the vertex buffer layouts and their attributes.
         * @param bufferLayouts The vertex buffer layouts.
         * @param count The number of vertex buffer layouts.
         */
        static void Delete(WGPUVertexBufferLayout *bufferLayouts, size_t count);
    };
}

#endif // !BNS_WEBGPU_BUFFER_LAYOUT_UTIL_HPP