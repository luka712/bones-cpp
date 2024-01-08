#if USE_VULKAN

#include "util/VulkanPipelineViewportStateCreateInfoUtil.hpp"

namespace bns
{
    VkPipelineViewportStateCreateInfo VulkanPipelineViewportStateCreateInfoUtil::Default()
    {
        // We use this in case if we do not want to set the viewport and scissor per pipeline and instead use global or per draw call
        // Dynamic state; set per draw call or global
        VkPipelineViewportStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        createInfo.viewportCount = 1;
        createInfo.pViewports = nullptr;
        createInfo.scissorCount = 1;
        createInfo.pScissors = nullptr;

        return createInfo;
    }

    VkPipelineViewportStateCreateInfo VulkanPipelineViewportStateCreateInfoUtil::Create(const VkViewport &viewport, const VkRect2D &scissor)
    {
        // viewport and scissor are not dynamic state, meaning they are set per pipeline

        VkPipelineViewportStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        createInfo.viewportCount = 1;
        createInfo.pViewports = &viewport;
        createInfo.scissorCount = 1;
        createInfo.pScissors = &scissor;

        return createInfo;
    }
} // namespace bns

#endif