#if USE_VULKAN

#ifndef BNS_VULKAN_BUFFER_UTIL_HPP

#define BNS_VULKAN_BUFFER_UTIL_HPP

#include "Types.hpp"
#include "BnsVulkan.hpp"
#include "ImageData.hpp"
#include <vector>

namespace bns
{
    /// @brief  A utility class for creating Vulkan buffers
    struct VulkanBufferUtil final
    {
        /// @brief Creates a @ref VkBuffer
        /// @param physicalDevice The physical device to create the buffer on
        /// @param device The device to create the buffer on
        /// @param size The size of the buffer
        /// @param usage The usage of the buffer
        /// @param outDeviceMemory The created memory for the buffer
        /// @param memoryPropertyFlags The memory property flags. By default this is @ref VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | @ref VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
        /// @return The created buffer
        static VkBuffer Create(const VkPhysicalDevice &physicalDevice,
                               const VkDevice &device,
                               VkDeviceSize size,
                               VkBufferUsageFlags usage,
                               VkDeviceMemory *outDeviceMemory,
                               VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        /// @brief Creates a @ref VkBuffer and writes data to it
        /// @param physicalDevice The physical device to create the buffer on
        /// @param device The device to create the buffer on
        /// @param data The data to copy to the buffer
        /// @param size The size of the buffer
        /// @param usage The usage of the buffer
        /// @param outDeviceMemory The created memory for the buffer
        /// @param memoryPropertyFlags The memory property flags. By default this is @ref VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | @ref VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
        /// @return The created buffer
        static VkBuffer Create(const VkPhysicalDevice &physicalDevice,
                               const VkDevice &device,
                               void *data,
                               VkDeviceSize size,
                               VkBufferUsageFlags usage,
                               VkDeviceMemory *outDeviceMemory,
                               VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        /// @brief Creates a @ref VkBuffer
        /// @param physicalDevice The physical device to create the buffer on
        /// @param device The device to create the buffer on
        /// @param size The size of the buffer
        /// @param outDeviceMemory The created memory for the buffer
        /// @return The created buffer
        static VkBuffer CreateVertexBuffer(const VkPhysicalDevice &physicalDevice, const VkDevice &device, VkDeviceSize size, VkDeviceMemory *outDeviceMemory);

        /// @brief Creates a @ref VkBuffer and writes data to it
        /// @param physicalDevice The physical device to create the buffer on
        /// @param device The device to create the buffer on
        /// @param data The data to copy to the buffer
        /// @param outDeviceMemory The created memory for the buffer
        /// @return The created buffer
        static VkBuffer CreateIndexBuffer(const VkPhysicalDevice &physicalDevice,
                                          const VkDevice &device,
                                          const std::vector<u16> &data,
                                          VkDeviceMemory *outDeviceMemory);

        /// @brief Creates a @ref VkBuffer
        /// @param physicalDevice The physical device to create the buffer on
        /// @param device The device to create the buffer on
        /// @param size The size of the buffer
        /// @param outDeviceMemory The created memory for the buffer
        /// @return The created buffer
        static VkBuffer CreateUniformBuffer(const VkPhysicalDevice &physicalDevice, const VkDevice &device, VkDeviceSize size, VkDeviceMemory *outDeviceMemory);

        /// @brief Creates a @ref VkBuffer
        /// @param physicalDevice The physical device to create the buffer on
        /// @param device The device to create the buffer on
        /// @param size The size of the buffer
        /// @param outDeviceMemory The created memory for the buffer
        /// @return The created buffer
        /// @note Used to transfer data to the GPU
        static VkBuffer CreateStagingBuffer(const VkPhysicalDevice &physicalDevice, const VkDevice &device, VkDeviceSize size, VkDeviceMemory *outDeviceMemory);

        /// @brief Copies a @ref VkBuffer to another @ref VkBuffer
        /// @param device The device to copy the buffer on
        /// @param commandPool The command pool to copy the buffer from
        /// @param queue The queue to copy the buffer to
        /// @param srcBuffer The source buffer
        /// @param dstBuffer The destination buffer
        /// @param size The size of the buffer to copy
        static void CopyBuffer(const VkDevice &device,
                               const VkCommandPool &commandPool,
                               const VkQueue &queue,
                               const VkBuffer &srcBuffer,
                               const VkBuffer &dstBuffer,
                               VkDeviceSize size);

        /// @brief Copies a @ref VkBuffer to a @ref VkImage
        /// @param device The device to copy the buffer on
        /// @param commandPool The command pool to copy the buffer from
        /// @param queue The queue to copy the buffer to
        /// @param srcBuffer The source buffer
        /// @param dstImage The destination image
        /// @param width The width of the image
        /// @param height The height of the image
        static void CopyBufferToImage(const VkDevice &device,
                                      const VkCommandPool &commandPool,
                                      const VkQueue &queue,
                                      const VkBuffer &srcBuffer,
                                      const VkImage &dstImage,
                                      u32 width, u32 height);

        /// @brief Destroys a @ref VkBuffer
        /// @param device The device to destroy the buffer on
        /// @param buffer The buffer to destroy
        static void Destroy(VkDevice &device, VkBuffer &buffer);
    };
}

#endif

#endif