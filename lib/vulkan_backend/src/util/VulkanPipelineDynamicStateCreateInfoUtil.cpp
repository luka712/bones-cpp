#if USE_VULKAN

#include "util/VulkanPipelineDynamicStateCreateInfoUtil.hpp"

namespace bns
{
    VkPipelineDynamicStateCreateInfo VulkanPipelineDynamicStateCreateInfoUtil::Create(const std::vector<VkDynamicState> &dynamicStates)
    {
        VkPipelineDynamicStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        createInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
        createInfo.pDynamicStates = dynamicStates.data();

        return createInfo;
    }
}

#endif