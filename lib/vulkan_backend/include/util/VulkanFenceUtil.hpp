#if USE_VULKAN

#ifndef VULKAN_FENCE_UTIL_HPP

#define VULKAN_FENCE_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns 
{
    /// @brief Utility functions for @ref VkFence
    struct VulkanFenceUtil
    {
        /// @brief Create a fence
        /// @param device The device that will own the fence
        /// @return The created fence
        static VkFence Create(VkDevice device);

        /// @brief Destroy a fence
        /// @param device The device that owns the fence
        /// @param fence The fence to destroy
        static void Destroy(VkDevice device, VkFence fence);
    };
}

#endif // VULKAN_FENCE_UTIL_HPP

#endif