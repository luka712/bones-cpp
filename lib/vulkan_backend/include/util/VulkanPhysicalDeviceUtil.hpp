#if USE_VULKAN

#ifndef VULKAN_PHYSICAL_DEVICE_UTIL_HPP

#define VULKAN_PHYSICAL_DEVICE_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>
#include <string>
#include "Types.hpp"

namespace bns 
{
    /// @brief Utility class for physical devices.
    struct VulkanPhysicalDeviceUtil
    {
    
        /// @brief Gets and prints the physical device extensions. 
        /// @param device The physical device to log the extensions for.
        /// @return The extensions as a vector of strings.
        static std::vector<std::string> GetDeviceExtensions(VkPhysicalDevice device);

        /// @brief Gets and prints the physical device properties.
        /// @param device The physical device to log the properties for.
        /// @return The physical device properties.
        static VkPhysicalDeviceProperties GetDeviceProperties(VkPhysicalDevice device);

        /// @brief Checks if the physical device supports the required extensions.
        /// @param device The physical device to check.
        /// @param requiredExtensions The required extensions.
        static bool IsDeviceSuitable(VkPhysicalDevice device, const std::vector<std::string>& requiredExtensions);

        /// @brief Enumerates all physical devices and returns the first one that supports the required extensions.
        /// @param instance The vulkan instance to use.
        /// @param requiredExtensions The required extensions.
        /// @return The first physical device that supports the required extensions. 
        static VkPhysicalDevice PickPhysicalDevice(VkInstance instance, const std::vector<std::string>& requiredExtensions);

        /// @brief Gets the queue family indices for the given physical device.
        /// @param device The physical device to get the queue family indices for.
        /// @param surface The surface to use.
        /// @param graphicsFamily The graphics family index.
        /// @param presentFamily The present family index.
        static void GetQueueFamilyIndices(VkPhysicalDevice device, VkSurfaceKHR surface, u32* graphicsFamily, u32* presentFamily);
    };
}

#endif 

#endif 