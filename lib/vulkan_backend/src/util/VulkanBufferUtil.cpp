#if USE_VULKAN

#include "util/VulkanBufferUtil.hpp"
#include <stdexcept>
#include <string>
#include "Types.hpp"
#include "BnsVulkan.hpp"

namespace bns
{
    VkBuffer VulkanBufferUtil::CreateVertexBuffer(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        VkDeviceSize size,
        VkDeviceMemory *outDeviceMemory)
    {
        VkBufferCreateInfo bufferCreateInfo = {};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.size = size;
        bufferCreateInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VkBuffer buffer;
        if (vkCreateBuffer(device, &bufferCreateInfo, nullptr, &buffer) != VK_SUCCESS)
        {
            std::string msg = "VulkanBufferUtil::CreateVertexBuffer: Failed to create vertex buffer";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        *outDeviceMemory = AllocateBufferMemory(physicalDevice, device, buffer);

        return buffer;
    }

    VkDeviceMemory VulkanBufferUtil::AllocateBufferMemory(const VkPhysicalDevice &physicalDevice, const VkDevice &device, VkBuffer &buffer)
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
        u32 properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
        {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
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
            std::string msg = "VulkanBufferUtil::AllocateBufferMemory: Failed to allocate buffer memory";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        vkBindBufferMemory(device, buffer, memory, 0);

        return memory;
    }

    void VulkanBufferUtil::WriteToDeviceMemory(const VkDevice &device, VkDeviceMemory &deviceMemory, void *data, VkDeviceSize size)
    {
        void *mappedMemory;
        vkMapMemory(device, deviceMemory, 0, size, 0, &mappedMemory);
        memcpy(mappedMemory, data, size);
        vkUnmapMemory(device, deviceMemory);
    }

    void VulkanBufferUtil::Destroy(VkDevice &device, VkBuffer &buffer)
    {
        vkDestroyBuffer(device, buffer, nullptr);
    }

    void VulkanBufferUtil::Free(VkDevice &device, VkDeviceMemory &memory)
    {
        vkFreeMemory(device, memory, nullptr);
    }
}

#endif