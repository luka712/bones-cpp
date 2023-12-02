#pragma once 

#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_VIEWPORT_STATE_CREATE_INFO_UTIL_HPP

#define BNS_VULKAN_PIPELINE_VIEWPORT_STATE_CREATE_INFO_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief The util class for working with @ref VkPipelineViewportStateCreateInfo
    struct VulkanPipelineViewportStateCreateInfoUtil final
    {   
        /// @brief Get the default @ref VkPipelineViewportStateCreateInfo. To be used when the viewport and scissor are dynamic state (set per draw call or global)
        /// @return The default @ref VkPipelineViewportStateCreateInfo. 
        static VkPipelineViewportStateCreateInfo Default();

        /// @brief Get the default @ref VkPipelineViewportStateCreateInfo. To be used when the viewport and scissor are set per pipeline.
        /// @param viewport The viewport.
        /// @param scissor The scissor.
        /// @return The default @ref VkPipelineViewportStateCreateInfo.
        static VkPipelineViewportStateCreateInfo Default(const VkViewport& viewport, const VkRect2D& scissor);
    };
} // namespace bns

#endif // !BNS_VULKAN_PIPELINE_VIEWPORT_STATE_CREATE_INFO_UTIL_HPP

#endif