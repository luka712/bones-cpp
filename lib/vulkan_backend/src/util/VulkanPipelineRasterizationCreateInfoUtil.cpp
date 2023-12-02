#if USE_VULKAN

#include "util/VulkanPipelineRasterizationCreateInfoUtil.hpp"

namespace bns
{
    VkPipelineRasterizationStateCreateInfo VulkanPipelineRasterizationCreateInfoUtil::Default()
    {
        VkPipelineRasterizationStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        createInfo.depthClampEnable = VK_FALSE;
        createInfo.rasterizerDiscardEnable = VK_FALSE;
        createInfo.polygonMode = VK_POLYGON_MODE_FILL;
        createInfo.lineWidth = 1.0f;
        createInfo.cullMode = VK_CULL_MODE_BACK_BIT;
        createInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
        createInfo.depthBiasEnable = VK_FALSE;
        createInfo.depthBiasConstantFactor = 0.0f; // Optional
        createInfo.depthBiasClamp = 0.0f;          // Optional
        createInfo.depthBiasSlopeFactor = 0.0f;    // Optional

        return createInfo;
    }
} // namespace bns

#endif 