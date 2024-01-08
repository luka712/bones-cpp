#if USE_VULKAN

#include "util/VulkanPipelineMultisampleStateCreateInfoUtil.hpp"

namespace bns
{
    VkPipelineMultisampleStateCreateInfo VulkanPipelineMultisampleStateCreateInfoUtil::Create()
    {
        VkPipelineMultisampleStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        createInfo.sampleShadingEnable = VK_FALSE;
        createInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        createInfo.minSampleShading = 1.0f;          // Optional
        createInfo.pSampleMask = nullptr;            // Optional
        createInfo.alphaToCoverageEnable = VK_FALSE; // Optional
        createInfo.alphaToOneEnable = VK_FALSE;      // Optional

        return createInfo;
    }

    VkPipelineMultisampleStateCreateInfo VulkanPipelineMultisampleStateCreateInfoUtil::CreateMSAADisabled()
    {
        // create a default create info with no multisampling disabled.
        return Create();
    }
} // namespace bns

#endif