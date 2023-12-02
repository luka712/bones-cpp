#pragma once 

#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO_UTIL_HPP

#define BNS_VULKAN_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkPipelineColorBlendStateCreateInfo.
    struct VulkanPipelineColorBlendStateCreateInfoUtil
    {
        /// @brief Creates a default @ref VkPipelineColorBlendStateCreateInfo.
        /// @param colorBlendAttachment The @ref VkPipelineColorBlendAttachmentState to use.
        /// @return The default @ref VkPipelineColorBlendStateCreateInfo.
        static VkPipelineColorBlendStateCreateInfo Create(const VkPipelineColorBlendAttachmentState& colorBlendAttachment);
    };
} // namespace bns

#endif

#endif