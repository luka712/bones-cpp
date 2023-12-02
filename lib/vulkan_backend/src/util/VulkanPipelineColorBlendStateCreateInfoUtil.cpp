#if USE_VULKAN

#include "util/VulkanPipelineColorBlendStateCreateInfoUtil.hpp"

namespace bns
{
    VkPipelineColorBlendStateCreateInfo VulkanPipelineColorBlendStateCreateInfoUtil::Create(const VkPipelineColorBlendAttachmentState& colorBlendAttachment)
    {
        VkPipelineColorBlendStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        createInfo.logicOpEnable = VK_FALSE;
        createInfo.logicOp = VK_LOGIC_OP_COPY; // Optional
        createInfo.attachmentCount = 1;
        createInfo.pAttachments = &colorBlendAttachment;
        createInfo.blendConstants[0] = 0.0f; // Optional
        createInfo.blendConstants[1] = 0.0f; // Optional
        createInfo.blendConstants[2] = 0.0f; // Optional
        createInfo.blendConstants[3] = 0.0f; // Optional

        return createInfo;
    }
} // namespace bns

#endif 