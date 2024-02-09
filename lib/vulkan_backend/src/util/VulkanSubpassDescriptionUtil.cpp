#if USE_VULKAN

#include "util/VulkanSubpassDescriptionUtil.hpp"
#include "bns_types.hpp"

namespace bns
{
    VkSubpassDescription VulkanSubpassDescriptionUtil::Create(const std::vector<VkAttachmentReference> &colorAttachmentRefs)
    {
        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = static_cast<u32>(colorAttachmentRefs.size());
        subpass.pColorAttachments = colorAttachmentRefs.data();
        subpass.pDepthStencilAttachment = nullptr;
        subpass.pInputAttachments = nullptr;
        subpass.pPreserveAttachments = nullptr;
        subpass.pResolveAttachments = nullptr;

        return subpass;
    }

    VkSubpassDescription VulkanSubpassDescriptionUtil::Create(const VkAttachmentReference &colorAttachmentRef)
    {
        std::vector<VkAttachmentReference> colorAttachmentRefs = {colorAttachmentRef};
        return Create(colorAttachmentRefs);
    }

    VkSubpassDescription VulkanSubpassDescriptionUtil::Create(const std::vector<VkAttachmentReference> &colorAttachmentRefs, const VkAttachmentReference &depthAttachmentRef)
    {
        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = static_cast<u32>(colorAttachmentRefs.size());
        subpass.pColorAttachments = colorAttachmentRefs.data();
        subpass.pDepthStencilAttachment = &depthAttachmentRef;
        subpass.pInputAttachments = nullptr;
        subpass.pPreserveAttachments = nullptr;
        subpass.pResolveAttachments = nullptr;

        return subpass;
    }

} // namespace bns

#endif