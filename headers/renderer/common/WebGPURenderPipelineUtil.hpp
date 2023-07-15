#ifndef BNS_WEBGPU_RENDER_PIPELINE_UTIL_HPP

#define BNS_WEBGPU_RENDER_PIPELINE_UTIL_HPP

#include <webgpu/webgpu.h>
#include <string>

namespace bns
{
    class WebGPURenderPipelineUtil
    {
    public:
        /**
         * @brief Create a render pipeline descriptor.
         * The render pipeline descriptor is used to describe the render pipeline.
         * @param pipelineLayout The pipeline layout to use.
         * @param vertexState The vertex state to use.
         * @param fragmentState The fragment state to use.
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
        static WGPURenderPipelineDescriptor CreatePipelineDescriptor(
            WGPUPipelineLayout pipelineLayout,
            WGPUVertexState vertexState,
            WGPUFragmentState fragmentState,
            WGPUPrimitiveTopology primitiveTopology = WGPUPrimitiveTopology::WGPUPrimitiveTopology_TriangleList,
            WGPUCullMode cullMode = WGPUCullMode::WGPUCullMode_None,
            std::string label = "render_pipeline");

        /**
         * @brief Create a shader module.
         * The shader module is used to describe the shader.
         * @param device The device to use.
         * @param source The source to use.
         * @param name The name to use. Default is "shader_module".
         * @return WGPUShaderModule The new shader module.
         *
         * @note The source is a string because it is easier to use.
         * @note The name is used for debugging.
         * @note The shader module is used to describe the shader.
         */
        static WGPUShaderModule CreateShaderModule(WGPUDevice device, std::string source, std::string label = "shader_module");
    };
}

#endif