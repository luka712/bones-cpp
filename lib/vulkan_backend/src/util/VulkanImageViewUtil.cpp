#if USE_VULKAN

#include "util/VulkanImageViewUtil.hpp"
#include <string>
#include <stdexcept>
#include "Types.hpp"

namespace bns 
{
    VkImageView VulkanImageViewUtil::Create(VkDevice device, VkImage image, VkFormat format)
    {


        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = image;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        VkImageView imageView;
        if (vkCreateImageView(device, &createInfo, nullptr, &imageView) != VK_SUCCESS) 
        {
            std::string msg = "VulkanImageViewUtil::Create: Failed to create image view!";
           LOG(msg); 
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return imageView;
    }

    void VulkanImageViewUtil::Destroy(VkDevice device, VkImageView imageView)
    {
        vkDestroyImageView(device, imageView, nullptr);
    }
}

#endif 