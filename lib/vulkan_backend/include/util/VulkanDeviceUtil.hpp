#if USE_VULKAN

#ifndef VULKAN_DEVICE_UTIL_HPP

#define VULKAN_DEVICE_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>
#include <string>

namespace bns
{
    /// @brief Utility class for creating @ref VkDevice structs
    struct VulkanDeviceUtil
    {
        /// @brief Creates a @see VkDevice
        /// @param physicalDevice The physical device to create the logical device from
        /// @param queueCreateInfos The queue create infos
        /// @param deviceFeatures The device features
        /// @param deviceExtensions The device extensions
        /// @param validationLayers The validation layers
        /// @return The created @see VkDevice
        static VkDevice Create(VkPhysicalDevice physicalDevice, 
            const std::vector<VkDeviceQueueCreateInfo>& queueCreateInfos, 
            const VkPhysicalDeviceFeatures& deviceFeatures, 
            const std::vector<std::string>& deviceExtensions,
            const std::vector<std::string>& validationLayers);
    };
}

#endif

#endif