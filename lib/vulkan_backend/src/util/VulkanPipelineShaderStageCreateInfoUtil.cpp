#if USE_VULKAN

#include "util/VulkanPipelineShaderStageCreateInfoUtil.hpp"

namespace bns
{
    void VulkanPipelineShaderStageCreateInfoUtil::SetVertexStageInfo(VkPipelineShaderStageCreateInfo &createInfo, const VkShaderModule& vertexShaderModule)
    {
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        createInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        createInfo.module = vertexShaderModule;
        createInfo.pName = "main";
        createInfo.pNext = nullptr;
        createInfo.pSpecializationInfo = nullptr;
    }

     void VulkanPipelineShaderStageCreateInfoUtil::SetFragmentStageInfo(VkPipelineShaderStageCreateInfo &createInfo, const VkShaderModule& fragmentShaderModule)
    {
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        createInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        createInfo.module = fragmentShaderModule;
        createInfo.pName = "main";
        createInfo.pNext = nullptr;
        createInfo.pSpecializationInfo = nullptr;
    }
}

#endif