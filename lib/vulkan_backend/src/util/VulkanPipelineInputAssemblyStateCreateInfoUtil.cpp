#if USE_VULKAN

#include "util/VulkanPipelineInputAssemblyStateCreateInfoUtil.hpp"

namespace bns
{
    VkPipelineInputAssemblyStateCreateInfo VulkanPipelineInputAssemblyStateCreateInfoUtil::Default()
    {
        VkPipelineInputAssemblyStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        createInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        createInfo.primitiveRestartEnable = VK_FALSE;

        return createInfo;
    }
} // namespace bns

#endif 