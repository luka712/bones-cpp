#if USE_VULKAN

#include "util/VulkanPipelineVertexInputStateCreateInfoUtil.hpp"
#include "Types.hpp"

namespace bns
{
    VkPipelineVertexInputStateCreateInfo VulkanPipelineVertexInputStateCreateInfoUtil::Create(
        const std::vector<VkVertexInputBindingDescription> &vertexInputBindingDescriptions,
        const std::vector<VkVertexInputAttributeDescription> &vertexInputAttributeDescriptions)
    {
        VkPipelineVertexInputStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        if (vertexInputBindingDescriptions.empty())
        {
            createInfo.vertexBindingDescriptionCount = 0;
            // throw small warning because this is not an error but it is not normal
            LOG("%s", "VulkanPipelineVertexInputStateCreateInfoUtil::Create: vertexInputBindingDescriptions is empty");
        }
        else
        {
            createInfo.vertexBindingDescriptionCount = static_cast<u32>(vertexInputBindingDescriptions.size());
            createInfo.pVertexBindingDescriptions = vertexInputBindingDescriptions.data();
        }

        if (vertexInputAttributeDescriptions.empty())
        {
            createInfo.vertexAttributeDescriptionCount = 0;
            // throw small warning because this is not an error but it is not normal
            LOG("%s", "VulkanPipelineVertexInputStateCreateInfoUtil::Create: vertexInputAttributeDescriptions is empty");
        }
        else
        {
            createInfo.vertexAttributeDescriptionCount = static_cast<u32>(vertexInputAttributeDescriptions.size());
            createInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();
        }

        return createInfo;
    }
}

#endif