#pragma once

#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_SHADER_STAGE_CREATE_INFO_HPP

#define BNS_VULKAN_PIPELINE_SHADER_STAGE_CREATE_INFO_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    struct VulkanPipelineShaderStageCreateInfoUtil
    {
        /// @brief Set the values of @see VkPipelineShaderStageCreateInfo to data for vertex shader stage.
        /// @param rCreateInfo The create info to be filled.
        /// @param vertexShaderModule The module for vertex shader stage.
        static void SetVertexStageInfo(VkPipelineShaderStageCreateInfo &rCreateInfo, VkShaderModule vertexShaderModule);

        /// @brief Set the values of @see VkPipelineShaderStageCreateInfo to data for fragment shader stage.
        /// @param rCreateInfo The create info to be filled.
        /// @param fragmentShaderModule The module for fragment shader stage.
        static void SetFragmentStageInfo(VkPipelineShaderStageCreateInfo &rCreateInfo, VkShaderModule fragmentShaderModule);
    };
}

#endif // BNS_VULKAN_PIPELINE_SHADER_STAGE_CREATE_INFO_HPP

#endif