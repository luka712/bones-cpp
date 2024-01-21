#if USE_VULKAN

#ifndef BNS_VULKAN_BUFFER_UTIL_HPP

#define BNS_VULKAN_BUFFER_UTIL_HPP

#include "Types.hpp"
#include "BnsVulkan.hpp"

namespace bns 
{
    /// @brief  A utility class for creating Vulkan buffers
    struct VulkanBufferUtil final 
    {
        /// @brief Creates a @ref VkBuffer 
        /// @param physicalDevice The physical device to create the buffer on
        /// @param device The device to create the buffer on
        /// @param size The size of the buffer
        /// @param outDeviceMemory The created memory for the buffer
        /// @return The created buffer
        static VkBuffer CreateVertexBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice &device, VkDeviceSize size, VkDeviceMemory *outDeviceMemory);

   
        /// @brief Creates a @ref VkBuffer
        /// @param physicalDevice The physical device to create the buffer on
        /// @param device The device to create the buffer on
        /// @param size The size of the buffer
        /// @param outDeviceMemory The created memory for the buffer
        /// @return The created buffer
        static VkBuffer CreateUniformBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice &device, VkDeviceSize size, VkDeviceMemory *outDeviceMemory);


        /// @brief Creates a @ref VkDeviceMemory for a @ref VkBuffer
        /// @param physicalDevice The physical device to create the memory on
        /// @param device The device to create the memory on
        /// @param buffer The buffer to create the memory for
        /// @return The created memory
        static VkDeviceMemory AllocateBufferMemory(const VkPhysicalDevice& physicalDevice, const VkDevice &device, VkBuffer &buffer);

        /// @brief Writes data to a @ref VkDeviceMemory
        /// @param device The device to write the data to
        /// @param deviceMemory The memory to write the data to
        /// @param data The data to write
        /// @param size The size of the data to write
        static void WriteToDeviceMemory(const VkDevice &device, VkDeviceMemory &deviceMemory, void *data, VkDeviceSize size);

        /// @brief Destroys a @ref VkBuffer
        /// @param device The device to destroy the buffer on
        /// @param buffer The buffer to destroy
        static void Destroy(VkDevice &device, VkBuffer &buffer);

        /// @brief Free a @ref VkDeviceMemory
        /// @param device The device to destroy the memory on
        /// @param memory The memory to destroy
        static void Free(VkDevice &device, VkDeviceMemory &memory);
    };
}

#endif 

#endif 