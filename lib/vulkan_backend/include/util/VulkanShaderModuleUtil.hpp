#pragma once

#if USE_VULKAN 

#ifndef BNS_VULKAN_SHADER_MODULE_UTIL_HPP

#define BNS_VULKAN_SHADER_MODULE_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>
#include <string>

namespace bns
{
    /// @brief The util class for working with @ref VkShaderModule
    struct VulkanShaderModuleUtil final
    {
        /// @brief Create a shader module from a binary SPIR-V code.
        /// @param device The device.
        /// @param code The binary SPIR-V code.
        /// @return The shader module.
        static VkShaderModule CreateFromSpirVSource(VkDevice device, const std::vector<char>& code);

        /// @brief Create a shader module from a SPIR-V file.
        /// @param device The device.
        /// @param filepath The filepath.
        /// @return The shader module.
        static VkShaderModule CreateFromSpirVFilepath(VkDevice device, std::string filepath);

        /// @brief Destroy the shader module.
        /// @param device The device.
        /// @param shaderModule The shader module.
        static void Destroy(VkDevice device, VkShaderModule shaderModule);
    };
} // namespace bns

#endif // !BNS_VULKAN_SHADER_MODULE_UTIL_HPP

#endif 