#if USE_VULKAN

#ifndef BNS_VULKAN_DEVICE_MEMORY_UTIL_HPP

#define BNS_VULKAN_DEVICE_MEMORY_UTIL_HPP

#include "bns_types.hpp"
#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief A utility class for working with @ref VkDeviceMemory
    /// https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDeviceMemory.html
    struct VulkanDeviceMemoryUtil final
    {

        /// @brief Allocates a @ref VkDeviceMemory for a @ref VkBuffer
        /// @param physicalDevice The physical device to allocate the memory on
        /// @param device The device to allocate the memory on
        /// @param buffer The buffer to allocate the memory for
        /// @param memoryPropertyFlags The memory property flags. By default this is @ref VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | @ref VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
        /// @return The allocated memory
        static VkDeviceMemory AllocateBufferMemory(
            const VkPhysicalDevice &physicalDevice,
            const VkDevice &device,
            const VkBuffer &buffer,
            VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        /// @brief Allocates a @ref VkDeviceMemory for a @ref VkImage
        /// @param physicalDevice The physical device to allocate the memory on
        /// @param device The device to allocate the memory on
        /// @param image The image to allocate the memory for
        /// @param memoryPropertyFlags The memory property flags
        /// @return The allocated memory
        /// @note Bind the memory to the image with @ref vkBindImageMemory
        static VkDeviceMemory AllocateImageMemory(
            const VkPhysicalDevice &physicalDevice,
            const VkDevice &device,
            const VkImage &image,
            VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        /// @brief Maps data data to a @ref VkDeviceMemory
        /// @param device The device to write the data to
        /// @param deviceMemory The memory to write the data to
        /// @param data The data to write
        /// @param size The size of the data to write
        static void Map(const VkDevice &device, VkDeviceMemory &deviceMemory, void *data, VkDeviceSize size);

        /// @brief Free a @ref VkDeviceMemory
        /// @param device The device to destroy the memory on
        /// @param memory The memory to destroy
        static void Free(VkDevice &device, VkDeviceMemory &memory);
    };
}

#endif

#endif