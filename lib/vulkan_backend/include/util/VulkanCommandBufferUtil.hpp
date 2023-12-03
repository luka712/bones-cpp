#if USE_VULKAN

#ifndef BNS_VULKAN_COMMAND_BUFFER_UTIL_HPP

#define BNS_VULKAN_COMMAND_BUFFER_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief Utility class for creating and destroying @ref VkCommandBuffer
    struct VulkanCommandBufferUtil
    {
        /// @brief Creates a @ref VkCommandBuffer
        /// @param device The device to create the command buffer on
        /// @param commandPool The command pool to create the command buffer from
        /// @param level The level of the command buffer
        /// @return The created command buffer
        static VkCommandBuffer Create(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
    };
} // namespace bns

#endif

#endif