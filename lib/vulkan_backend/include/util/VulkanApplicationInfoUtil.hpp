#if USE_VULKAN

#ifndef VULKAN_APPLICATION_INFO_UTIL_HPP

#define VULKAN_APPLICATION_INFO_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief Utility class for @ref VkApplicationInfo struct
    struct VulkanApplicationInfoUtil
    {
        /// @brief Creates @ref VkApplicationInfo struct with default values
        /// @return The created @ref VkApplicationInfo struct
        static VkApplicationInfo Create();
    };
}

#endif // !VULKAN_APPLICATION_INFO_UTIL_HPP

#endif