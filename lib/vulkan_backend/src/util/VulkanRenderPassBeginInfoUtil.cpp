#if USE_VULKAN

#include "util/VulkanRenderPassBeginInfoUtil.hpp"

namespace bns
{
    VkRenderPassBeginInfo VulkanRenderPassBeginInfoUtil::Create(VkRenderPass renderPass, 
                                                                VkFramebuffer framebuffer, 
                                                                VkExtent2D swapChainExtent, 
                                                                const VkClearValue& clearColor)
    {
        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

        // Render pass
        renderPassInfo.renderPass = renderPass;
        renderPassInfo.framebuffer = framebuffer;

        // Render area
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChainExtent;

        // Clear color
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        return renderPassInfo;
    }
} // namespace bns

#endif 