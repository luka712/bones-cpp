#if USE_VULKAN

#ifndef VULKAN_DEVICE_QUEUE_CREATE_INFO_UTIL_HPP

#define VULKAN_DEVICE_QUEUE_CREATE_INFO_UTIL_HPP

#include "BnsVulkan.hpp"
#include "Types.hpp"
#include <vector>

namespace bns
{
    /// @brief Utility class for creating @ref VkDeviceQueueCreateInfo structs
    struct VulkanDeviceQueueCreateInfoUtil
    {
        /// @brief Creates a @see VkDeviceQueueCreateInfo
        /// @param queueFamilyIndex The queue family index
        /// @param queuePriorities The queue priorities
        /// @return The created @see VkDeviceQueueCreateInfo
        static VkDeviceQueueCreateInfo Create(u32 queueFamilyIndex, const std::vector<f32> &queuePriorities);
    };
}

#endif

#endif