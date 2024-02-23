#if USE_WEBGPU

#ifndef BNS_WEBGPU_RENDER_PIPELINE_UTIL

#define BNS_WEBGPU_RENDER_PIPELINE_UTIL

#include "bns_webgpu.hpp"
#include "buffer_layout/BufferLayoutData.hpp"
#include <vector>
#include <string>

namespace bns
{
    /// @brief The WebGPU render pipeline util.
    class WebGPURenderPipelineUtil final
    {
    private:
        /// @brief Resolve the step mode.
        /// @param stepMode The step mode.
        /// @return The WGPUVertexStepMode.
        static WGPUVertexStepMode ResolveStepMode(VertexStepMode stepMode);

        /// @brief Resolve the vertex format.
        /// @param format The format.
        /// @return The WGPUVertexFormat.
        static WGPUVertexFormat ResolveVertexFormat(VertexFormat format);

    public:
        /// @brief Create a new render pipeline.
        /// @param device The device.
        /// @param shaderModule The shader module.
        /// @param pipelineLayout The pipeline layout.
        /// @param vertexBufferLayouts The vertex buffer layouts.
        /// @param vertexEntryPoint The vertex entry point. Default is "main_vs".
        /// @param fragmentEntryPoint The fragment entry point. Default is "main_fs".
        /// @param label The label. Default is "render_pipeline".
        /// @return The render pipeline.
        static WGPURenderPipeline Create(
            WGPUDevice device,
            WGPUShaderModule shaderModule,
            WGPUPipelineLayout pipelineLayout,
            std::vector<BufferLayoutDescriptor> vertexBufferLayouts,
            std::string vertexEntryPoint = "main_vs",
            std::string fragmentEntryPoint = "main_fs",
            std::string label = "");

        /// @brief Dispose of a render pipeline.
        /// @param renderPipeline The render pipeline.
        static void Dispose(WGPURenderPipeline renderPipeline);
    };
}

#endif

#endif