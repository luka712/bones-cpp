#pragma once 

#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_COLOR_BLEND_ATTACHMENT_STATE_UTIL_HPP

#define BNS_VULKAN_PIPELINE_COLOR_BLEND_ATTACHMENT_STATE_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkPipelineColorBlendAttachmentState.
    struct VulkanPipelineColorBlendAttachmentStateUtil
    {
        /// @brief Creates a default @ref VkPipelineColorBlendAttachmentState.
        /// @return The default @ref VkPipelineColorBlendAttachmentState.
        static VkPipelineColorBlendAttachmentState Create();
    };
} // namespace bns

#endif 

#endif 