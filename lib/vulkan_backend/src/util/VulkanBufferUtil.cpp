#if USE_VULKAN

#include "util/VulkanBufferUtil.hpp"
#include <stdexcept>
#include <string>
#include "Types.hpp"
#include "BnsVulkan.hpp"
#include "VulkanUtil.hpp"

namespace bns
{
    VkBuffer VulkanBufferUtil::Create(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkDeviceMemory *outDeviceMemory,
        VkMemoryPropertyFlags memoryPropertyFlags)
    {
        VkBuffer buffer;
        VkBufferCreateInfo bufferCreateInfo = {};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.size = size;
        bufferCreateInfo.usage = usage;
        bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufferCreateInfo, nullptr, &buffer) != VK_SUCCESS)
        {
            std::string msg = "VulkanBufferUtil::Create: Failed to create buffer.";
            LOG( msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        *outDeviceMemory = VulkanUtil::DeviceMemory.AllocateBufferMemory(physicalDevice, device, buffer, memoryPropertyFlags);

        return buffer;
    }

    VkBuffer VulkanBufferUtil::Create(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        void *data,
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkDeviceMemory *outDeviceMemory,
        VkMemoryPropertyFlags memoryPropertyFlags)
    {
        VkBuffer buffer = Create(physicalDevice, device, size, usage, outDeviceMemory, memoryPropertyFlags);
        VulkanUtil::DeviceMemory.Map(device, *outDeviceMemory, data, size);
        return buffer;
    }
  
    VkBuffer VulkanBufferUtil::CreateVertexBuffer(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        VkDeviceSize size,
        VkDeviceMemory *outDeviceMemory)
    {
        return Create(physicalDevice, device, size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, outDeviceMemory);
    }

      VkBuffer VulkanBufferUtil::CreateIndexBuffer(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        const std::vector<u16> &data,
        VkDeviceMemory *outDeviceMemory)
    {
        VkDeviceSize size = data.size() * sizeof(u16);
        return Create(physicalDevice, device, (void*)data.data(), size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, outDeviceMemory);
    }


    VkBuffer VulkanBufferUtil::CreateUniformBuffer(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        VkDeviceSize size,
        VkDeviceMemory *outDeviceMemory)
    {
        return Create(physicalDevice, device, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, outDeviceMemory);
    }

    VkBuffer VulkanBufferUtil::CreateStagingBuffer(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        VkDeviceSize size,
        VkDeviceMemory *outDeviceMemory)
    {
        return Create(physicalDevice, device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, outDeviceMemory);
    }

    void VulkanBufferUtil::CopyBuffer(const VkDevice &device,
                                      const VkCommandPool &commandPool,
                                      const VkQueue &queue,
                                      const VkBuffer &srcBuffer,
                                      const VkBuffer &dstBuffer,
                                      VkDeviceSize size)
    {
        // we need to create a command buffer to copy the buffer. This will allocate and destroy the command buffer.
        VulkanUtil::CommandBuffer.SingleTimeCommand(device, commandPool, queue,
                                                    [&](const VkCommandBuffer &commandBuffer)
                                                    {
                                                        VkBufferCopy copyRegion = {};
                                                        copyRegion.size = size;
                                                        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
                                                    });
    }

    void VulkanBufferUtil::CopyBufferToImage(const VkDevice &device,
                                             const VkCommandPool &commandPool,
                                             const VkQueue &queue,
                                             const VkBuffer &srcBuffer,
                                             const VkImage &dstImage,
                                             u32 width, u32 height)
    {
        // we need to create a command buffer to copy the buffer. This will allocate and destroy the command buffer.
        VulkanUtil::CommandBuffer.SingleTimeCommand(device, commandPool, queue,
                                                    [&](const VkCommandBuffer &commandBuffer)
                                                    {
                                                        VkBufferImageCopy region = {};
                                                        region.bufferOffset = 0;
                                                        region.bufferRowLength = 0;
                                                        region.bufferImageHeight = 0;
                                                        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                                                        region.imageSubresource.mipLevel = 0;
                                                        region.imageSubresource.baseArrayLayer = 0;
                                                        region.imageSubresource.layerCount = 1;
                                                        region.imageOffset = {0, 0, 0};
                                                        region.imageExtent = {width, height, 1};

                                                        vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
                                                    });
    }

    void VulkanBufferUtil::Destroy(VkDevice &device, VkBuffer &buffer)
    {
        vkDestroyBuffer(device, buffer, nullptr);
    }

}

#endif