#ifndef BNS_WEBGPU_VERTEX_BUFFER_LAYOUT_UTIL_HPP

#define BNS_WEBGPU_VERTEX_BUFFER_LAYOUT_UTIL_HPP

#include <webgpu/webgpu.h>
#include <vector>
#include <map>
#include "buffer-layout/BufferLayoutData.hpp"
namespace bns
{
    
    class WebGPUVertexBufferLayoutUtil final
    {
    private:
        inline static std::map<VertexFormat, WGPUVertexFormat> m_vertexFormatMap = {
            {VertexFormat::Float32x2, WGPUVertexFormat::WGPUVertexFormat_Float32x2},
            {VertexFormat::Float32x3, WGPUVertexFormat::WGPUVertexFormat_Float32x3},
            {VertexFormat::Float32x4, WGPUVertexFormat::WGPUVertexFormat_Float32x4}};

        inline static std::map<StepMode, WGPUVertexStepMode> m_vertexStepModeMap = {
            {StepMode::Vertex, WGPUVertexStepMode::WGPUVertexStepMode_Vertex}};

    public:
        /**
         * @brief Create a vertex buffer layout.
         * @return The vertex buffer layout.
         */
        static WGPUVertexBufferLayout* CreateVertexBufferLayouts(std::vector<BufferLayoutDescriptor> &descriptors);

        /**
         * @brief Delete the vertex buffer layouts and their attributes.
         * @param bufferLayouts The vertex buffer layouts.
         * @param count The number of vertex buffer layouts.
         */
        static void DeleteVertexBufferLayouts(WGPUVertexBufferLayout *bufferLayouts, size_t count);
    };
}

#endif // !BNS_WEBGPU_BUFFER_LAYOUT_UTIL_HPP