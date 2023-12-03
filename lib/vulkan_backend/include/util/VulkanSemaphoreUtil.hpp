#if USE_VULKAN

#ifndef VULKAN_SEMAPHORE_UTIL_HPP

#define VULKAN_SEMAPHORE_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns 
{
    struct VulkanSemaphoreUtil
    {
        /// @brief Create a semaphore
        /// @param device The device that will own the semaphore
        /// @return The created semaphore
        static VkSemaphore Create(VkDevice device);

        /// @brief Destroy a semaphore
        /// @param device The device that owns the semaphore
        /// @param semaphore The semaphore to destroy
        static void Destroy(VkDevice device, VkSemaphore semaphore);
    };
}

#endif // VULKAN_SEMAPHORE_UTIL_HPP

#endif 