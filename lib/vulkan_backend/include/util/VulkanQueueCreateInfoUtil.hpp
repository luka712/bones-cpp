#if USE_VULKAN

#ifndef VULKAN_QUEUE_CREATE_INFO_UTIL_HPP

#define VULKAN_QUEUE_CREATE_INFO_UTIL_HPP

#include "BnsVulkan.hpp"
#include "bns_types.hpp"
#include <vector>

namespace bns
{
    /// @brief Utility class for creating @ref VkDeviceQueueCreateInfo structs
    struct VulkanQueueCreateInfoUtil
    {
        /// @brief Create a VkDeviceQueueCreateInfo struct
        /// @param queueFamilyIndex The index of the queue family to create
        /// @param queuePriorities The priorities of the queues to create.
        /// @return The created @ref VkDeviceQueueCreateInfo struct
        static VkDeviceQueueCreateInfo Create(u32 queueFamilyIndex, const std::vector<f32>& queuePriorities);
    };
}

#endif

#endif