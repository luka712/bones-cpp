#ifndef BNS_WEBGPU_RENDER_PIPELINE_DESCRIPTOR_UTIL_HPP

#define BNS_WEBGPU_RENDER_PIPELINE_DESCRIPTOR_UTIL_HPP

#include <string>
#include <webgpu/webgpu.h>

namespace bns
{
    struct WebGPURenderPipelineDescriptorUtil final
    {
        /**
         * @brief Create a render pipeline descriptor.
         * The render pipeline descriptor is used to describe the render pipeline.
         * @param pipelineLayout The pipeline layout to use.
         * @param vertexState The vertex state to use.
         * @param fragmentState The fragment state to use.
         * @param depthStencilState The depth stencil state to use. By default nullptr and not set.
         * @param primitiveTopology The primitive topology to use.
         * @param cullMode The cull mode to use.
         * @param label The label to use. Default is "render_pipeline".
         * @return WGPURenderPipelineDescriptor The new render pipeline descriptor.
         *
         * @note The label is used for debugging.
         * @note The render pipeline descriptor is used to describe the render pipeline.
         * @note The vertex state is used to describe the vertex shader.
         * @note The fragment state is used to describe the fragment shader.
         * @note The primitive topology is used to describe the primitive topology.
         * @note The cull mode is used to describe the cull mode.
         * @note The pipeline layout is used to describe the pipeline layout.
         */
        static WGPURenderPipelineDescriptor Create(
            WGPUPipelineLayout pipelineLayout,
            WGPUVertexState vertexState,
            WGPUFragmentState fragmentState,
            WGPUDepthStencilState* depthStencilState = nullptr,
            WGPUPrimitiveTopology primitiveTopology = WGPUPrimitiveTopology::WGPUPrimitiveTopology_TriangleList,
            WGPUCullMode cullMode = WGPUCullMode::WGPUCullMode_None,
            std::string label = "render_pipeline");
    };
} // namespace bns

#endif
