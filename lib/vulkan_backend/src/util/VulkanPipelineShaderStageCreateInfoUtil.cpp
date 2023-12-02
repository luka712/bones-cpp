#if USE_VULKAN

#include "util/VulkanPipelineShaderStageCreateInfoUtil.hpp"

namespace bns
{
    void VulkanPipelineShaderStageCreateInfoUtil::SetVertexStageInfo(VkPipelineShaderStageCreateInfo &rCreateInfo, VkShaderModule vertexShaderModule)
    {
        rCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        rCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;

        // entry point
        rCreateInfo.module = vertexShaderModule;
        rCreateInfo.pName = "main";
    }

     void VulkanPipelineShaderStageCreateInfoUtil::SetFragmentStageInfo(VkPipelineShaderStageCreateInfo &rCreateInfo, VkShaderModule fragmentShaderModule)
    {
        rCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        rCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

        // entry point
        rCreateInfo.module = fragmentShaderModule;
        rCreateInfo.pName = "main";
    }
}

#endif