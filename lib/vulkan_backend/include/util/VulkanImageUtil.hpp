#if USE_VULKAN

#ifndef BNS_VULKAN_IMAGE_UTIL_HPP

#define BNS_VULKAN_IMAGE_UTIL_HPP

#include "bns_types.hpp"
#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief A utility class for working with @ref VkImage
    struct VulkanImageUtil
    {
        /// @brief Creates a @ref VkImage
        /// @param physicalDevice The physical device to create the image on
        /// @param device The device to create the image on
        /// @param width The width of the image
        /// @param height The height of the image
        /// @param outDeviceMemory The created memory for the image
        /// @return The created image
        static VkImage Create(
            const VkPhysicalDevice &physicalDevice,
            const VkDevice &device,
            u32 width, u32 height,
            VkDeviceMemory *outDeviceMemory);
        
        /// @brief Copies a @ref VkBuffer to a @ref VkImage
        /// @param device The device to copy the buffer on
        /// @param commandPool The command pool to copy the buffer from
        /// @param queue The queue to copy the buffer to
        /// @param buffer The buffer to copy
        /// @param image The image to copy to
        /// @param width The width of the image
        /// @param height The height of the image
        static void CopyBufferToImage(
            const VkDevice &device,
            const VkCommandPool &commandPool,
            const VkQueue &queue,
            const VkBuffer &buffer,
            const VkImage &image,
            u32 width, u32 height);
    };
}

#endif

#endif