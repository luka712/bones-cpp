#if USE_VULKAN

#ifndef BNS_VULKAN_IMAGE_LAYOUT_UTIL_HPP

#define BNS_VULKAN_IMAGE_LAYOUT_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief A utility class for working with @ref VkImageLayout
    struct VulkanImageLayoutUtil final
    {
        /// @brief Transitions the image layout.
        /// @param device The device.
        /// @param commandPool The command pool.
        /// @param queue The queue.
        /// @param image The image.
        /// @param format The format.
        /// @param oldLayout The old layout.
        /// @param newLayout The new layout.
        static void TransitionImageLayout(
            const VkDevice &device,
            const VkCommandPool &commandPool,
            const VkQueue &queue,
            const VkImage &image,
            VkFormat format,
            VkImageLayout oldLayout,
            VkImageLayout newLayout);
    };
}

#endif

#endif