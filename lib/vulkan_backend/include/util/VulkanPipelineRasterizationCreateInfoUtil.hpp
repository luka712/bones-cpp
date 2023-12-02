#pragma once 

#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_RASTERIZATION_CREATE_INFO_UTIL_HPP

#define BNS_VULKAN_PIPELINE_RASTERIZATION_CREATE_INFO_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief The util class for working with @ref VkPipelineRasterizationStateCreateInfo
    struct VulkanPipelineRasterizationCreateInfoUtil final
    {
        /// @brief Get the default @ref VkPipelineRasterizationStateCreateInfo.
        /// @return The default @ref VkPipelineRasterizationStateCreateInfo.
        static VkPipelineRasterizationStateCreateInfo Default();
    };
} // namespace bns

#endif // !BNS_VULKAN_PIPELINE_RASTERIZATION_CREATE_INFO_UTIL_HPP

#endif // !USE_VULKAN
