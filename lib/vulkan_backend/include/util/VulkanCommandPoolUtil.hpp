#if USE_VULKAN

#ifndef BNS_VULKAN_COMMAND_POOL_UTIL_HPP
#define BNS_VULKAN_COMMAND_POOL_UTIL_HPP

#include "BnsVulkan.hpp"
#include "bns_types.hpp"

namespace bns
{
    /// @brief Utility class for creating and destroying @ref VkCommandPool
    struct VulkanCommandPoolUtil
    {
        /// @brief Creates a @ref VkCommandPool
        /// @param device The device to create the command pool on
        /// @param queueFamilyIndex The queue family index to create the command pool for. Usually the graphics queue
        /// @param flags The flags to create the command pool with
        /// @return The created command pool
        static VkCommandPool Create(VkDevice device, u32 queueFamilyIndex, VkCommandPoolCreateFlags flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

        /// @brief Destroys a command pool
        /// @param device The device to destroy the command pool on
        /// @param commandPool The command pool to destroy
        static void Destroy(VkDevice device, VkCommandPool commandPool);
    };
} // namespace bns

#endif 

#endif 