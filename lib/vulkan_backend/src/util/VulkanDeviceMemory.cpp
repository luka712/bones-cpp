#if USE_VULKAN

#include "util/VulkanDeviceMemory.hpp"
#include <stdexcept>
#include <string>

namespace bns
{
    VkDeviceMemory VulkanDeviceMemoryUtil::AllocateBufferMemory(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        const VkBuffer &buffer,
        VkMemoryPropertyFlags memoryPropertyFlags)
    {
        // Get memory requirements
        VkMemoryRequirements memoryRequirements;
        vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);

        // Get memory properties
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        // Find memory type index
        u32 memoryTypeIndex = 0;
        u32 typeFilter = memoryRequirements.memoryTypeBits;
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
        {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & memoryPropertyFlags) == memoryPropertyFlags)
            {
                {
                    memoryTypeIndex = i;
                    break;
                }
            }
        }

        VkMemoryAllocateInfo memoryAllocateInfo = {};
        memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.allocationSize = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = memoryTypeIndex;

        VkDeviceMemory memory;
        if (vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &memory) != VK_SUCCESS)
        {
            std::string msg = "VulkanBufferUtil::AllocateBufferMemory: Failed to allocate buffer memory.";
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        vkBindBufferMemory(device, buffer, memory, 0);

        return memory;
    }

    VkDeviceMemory VulkanDeviceMemoryUtil::AllocateImageMemory(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        const VkImage &image,
        VkMemoryPropertyFlags memoryPropertyFlags)
    {
        VkMemoryRequirements memoryRequirements;
        vkGetImageMemoryRequirements(device, image, &memoryRequirements);

        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        u32 memoryTypeIndex = 0;
        u32 typeFilter = memoryRequirements.memoryTypeBits;
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
        {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & memoryPropertyFlags) == memoryPropertyFlags)
            {
                {
                    memoryTypeIndex = i;
                    break;
                }
            }
        }

        VkMemoryAllocateInfo memoryAllocateInfo = {};
        memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.allocationSize = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = memoryTypeIndex;

        VkDeviceMemory memory;
        if (vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &memory) != VK_SUCCESS)
        {
            std::string msg = "VulkanBufferUtil::AllocateImageMemory: Failed to allocate image memory.";
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        vkBindImageMemory(device, image, memory, 0);

        return memory;
    }

    void VulkanDeviceMemoryUtil::Map(const VkDevice &device, VkDeviceMemory &deviceMemory, void *data, VkDeviceSize size)
    {
        void *mappedMemory;
        vkMapMemory(device, deviceMemory, 0, size, 0, &mappedMemory);
        memcpy(mappedMemory, data, size);
        vkUnmapMemory(device, deviceMemory);
    }

    void VulkanDeviceMemoryUtil::Free(VkDevice &device, VkDeviceMemory &memory)
    {
        vkFreeMemory(device, memory, nullptr);
    }
}

#endif