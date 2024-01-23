#if USE_VULKAN

#ifndef BNS_VULKAN_COMMAND_BUFFER_UTIL_HPP

#define BNS_VULKAN_COMMAND_BUFFER_UTIL_HPP

#include "BnsVulkan.hpp"
#include <functional>

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
        static VkCommandBuffer Create(const VkDevice &device, const VkCommandPool &commandPool, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

        /// @brief Creates a single time command buffer. It is created and destroyed within this function
        /// @param device The device to create the command buffer on
        /// @param commandPool The command pool to create the command buffer from
        /// @param queue The queue to submit the command buffer to
        /// @param callback The callback to execute on the command buffer
        static void SingleTimeCommand(const VkDevice &device, const VkCommandPool &commandPool, const VkQueue &queue, std::function<void(const VkCommandBuffer &)> callback);
    };
} // namespace bns

#endif

#endif