#if USE_VULKAN

#ifndef BNS_VULKAN_DEBUG_UTILS_MESSENGER_EXT_UTIL_HPP
#define BNS_VULKAN_DEBUG_UTILS_MESSENGER_EXT_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkDebugUtilsMessengerEXT
    struct VulkanDebugUtilsMessengerEXTUtil
    {
        /// @brief Creates the debug utils messenger. This is used to debug the Vulkan API.
        /// @param instance The Vulkan instance.
        /// @param callback The callback.
        /// @param pUserData The user data. By default nullptr.
        /// @return The debug utils messenger.
        static VkDebugUtilsMessengerEXT Create(VkInstance instance, PFN_vkDebugUtilsMessengerCallbackEXT callback, void *pUserData = nullptr);
    };
}

#endif

#endif