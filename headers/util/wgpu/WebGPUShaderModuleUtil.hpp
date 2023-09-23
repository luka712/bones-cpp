#ifndef BNS_WEBGPU_SHADER_MODULE_UTIL_HPP

#define BNS_WEBGPU_SHADER_MODULE_UTIL_HPP

#include <string>
#include <webgpu/webgpu.h>

namespace bns
{
    struct WebGPUShaderModuleUtil final
    {
        /**
         * @brief Create a shader module from a string.
         * @param device The device to use.
         * @param shader The shader to use.
         * @param label The label to use. Default is "shader_module".
         * @return The shader module.
         * @note The label is used for debugging.
         * @note The shader module is used to describe the shader module.
         * @note The shader is used to describe the shader.
         */
        static WGPUShaderModule Create(WGPUDevice device, const std::string& shaderSource, std::string label = "shader_module");
    };
}

#endif // !BNS_WEBGPU_SHADER_MODULE_UTIL_HPP