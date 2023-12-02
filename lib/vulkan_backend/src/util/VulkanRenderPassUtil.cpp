#if USE_VULKAN

#include "util/VulkanRenderPassUtil.hpp"
#include "Types.hpp"
#include <stdexcept>
#include <string>

namespace bns
{
    VkRenderPass VulkanRenderPassUtil::Create(const VkDevice& device,
                                              const std::vector<VkAttachmentDescription> &attachmentDescriptions,
                                              const std::vector<VkSubpassDescription> &subpassDescriptions)
    {
        VkRenderPassCreateInfo renderPassCreateInfo{};
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.attachmentCount = static_cast<u32>(attachmentDescriptions.size());
        renderPassCreateInfo.pAttachments = attachmentDescriptions.data();
        renderPassCreateInfo.subpassCount = static_cast<u32>(subpassDescriptions.size());
        renderPassCreateInfo.pSubpasses = subpassDescriptions.data();

        VkRenderPass renderPass;
        if(vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &renderPass) != VK_SUCCESS)
        {
            std::string msg = "VulkanRenderPassUtil::Create: failed to create render pass!";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return renderPass;
    }

    void VulkanRenderPassUtil::Destroy(const VkDevice& device,
                                       const VkRenderPass& renderPass)
    {
        vkDestroyRenderPass(device, renderPass, nullptr);
    }
}

#endif