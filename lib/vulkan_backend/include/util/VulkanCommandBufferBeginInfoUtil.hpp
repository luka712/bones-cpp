#if USE_VULKAN

#ifndef BNS_VULKAN_COMMAND_BUFFER_BEGIN_INFO_UTIL_HPP

#define BNS_VULKAN_COMMAND_BUFFER_BEGIN_INFO_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkCommandBufferBeginInfo
    struct VulkanCommandBufferBeginInfoUtil
    {

        /// @brief Creates a @ref VkCommandBufferBeginInfo
        static VkCommandBufferBeginInfo Create();
    };
} // namespace bns

#endif

#endif