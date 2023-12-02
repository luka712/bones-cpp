#if USE_VULKAN

#include "util/VulkanAttachmentReferenceUtil.hpp"

namespace bns
{
    VkAttachmentReference VulkanAttachmentReferenceUtil::CreateColorAttachmentRef(u32 attachmentLocation)
    {
        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = attachmentLocation; // in glsl this is for example "layout(location = 0) out vec4 outColor"
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        return colorAttachmentRef;
    }
} // namespace bns

#endif 