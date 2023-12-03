#if USE_VULKAN

#include "util/VulkanFramebufferUtil.hpp"
#include <string>
#include <stdexcept>

namespace bns
{

    VkFramebuffer VulkanFramebufferUtil::Create(VkDevice device, VkRenderPass renderPass, VkImageView imageView, VkExtent2D swapChainExtent)
    {
        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = &imageView;
        framebufferInfo.width = swapChainExtent.width;
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;

        VkFramebuffer framebuffer;
        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffer) != VK_SUCCESS)
        {
            std::string msg = "VulkanFramebufferUtil::CreateFramebuffer: failed to create framebuffer!";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return framebuffer;
    }

    std::vector<VkFramebuffer> VulkanFramebufferUtil::Create(VkDevice device, VkRenderPass renderPass, std::vector<VkImageView> imageViews, VkExtent2D swapChainExtent)
    {
        std::vector<VkFramebuffer> framebuffers(imageViews.size());

        for (size_t i = 0; i < imageViews.size(); i++)
        {
            framebuffers[i] = Create(device, renderPass, imageViews[i], swapChainExtent);
        }

        return framebuffers;
    }

    void VulkanFramebufferUtil::Destroy(VkDevice device, VkFramebuffer framebuffer)
    {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }

}

#endif