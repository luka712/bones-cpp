#if USE_VULKAN

#include "util/VulkanImageUtil.hpp"
#include "VulkanUtil.hpp"
#include <stdexcept>
#include <string>

namespace bns
{
    VkImage VulkanImageUtil::Create(
        const VkPhysicalDevice &physicalDevice,
        const VkDevice &device,
        u32 width, u32 height,
        VkDeviceMemory *outDeviceMemory)
    {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.flags = 0; // Optional

        VkImage image;
        if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS)
        {
            std::string msg = "VulkanImageUtil::Create: Failed to create image.";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        *outDeviceMemory = VulkanUtil::DeviceMemory.AllocateImageMemory(physicalDevice, device, image);

        return image;
    }

    void VulkanImageUtil::CopyBufferToImage(
        const VkDevice &device,
        const VkCommandPool &commandPool,
        const VkQueue &queue,
        const VkBuffer &buffer,
        const VkImage &image,
        u32 width, u32 height)
    {
        VulkanUtil::Buffer.CopyBufferToImage(device, commandPool, queue, buffer, image, width, height);
    }
}

#endif