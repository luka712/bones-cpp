#if USE_VULKAN

#include "util/VulkanPipelineInputAssemblyStateCreateInfoUtil.hpp"

namespace bns
{
    VkPipelineInputAssemblyStateCreateInfo VulkanPipelineInputAssemblyStateCreateInfoUtil::Default()
    {
        VkPipelineInputAssemblyStateCreateInfo createInfo{};
        createInfo.pNext = nullptr;
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        createInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        createInfo.primitiveRestartEnable = VK_FALSE;

        return createInfo;
    }

    VkPipelineInputAssemblyStateCreateInfo VulkanPipelineInputAssemblyStateCreateInfoUtil::CreateWithTriangleListTopology()
    {
        return Default();
    }
} // namespace bns

#endif 