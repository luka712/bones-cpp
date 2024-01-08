#if USE_VULKAN

#ifndef VULKAN_IMAGE_VIEW_UTIL_HPP

#define VULKAN_IMAGE_VIEW_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns 
{
    /// @brief The vulkan image view util.
    struct VulkanImageViewUtil
    {
        /// @brief Creates the default image view. This is a 2D image view. 
        /// @param device The vulkan device.
        /// @param image The vulkan image.
        /// @param format The vulkan format.
        /// @return The vulkan image view.
        static VkImageView Create(VkDevice device, VkImage image, VkFormat format);

        /// @brief Destroys the vulkan image view.
        /// @param device The vulkan device.
        /// @param imageView The vulkan image view.
        static void Destroy(VkDevice device, VkImageView imageView);
    };
}

#endif 

#endif 