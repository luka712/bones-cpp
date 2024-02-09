#if USE_VULKAN

#include "util/VulkanPipelineLayoutUtil.hpp"
#include "bns_types.hpp"
#include <string>
#include <stdexcept>

namespace bns
{
    VkPipelineLayout VulkanPipelineLayoutUtil::Create(VkDevice device,
                                                      const std::vector<VkDescriptorSetLayout> &descriptorSetLayout,
                                                      const std::vector<VkPushConstantRange> &pushConstantRanges)
    {
        VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;

        VkPushConstantRange pushConstantRange{};

        VkPipelineLayoutCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        createInfo.setLayoutCount = static_cast<u32>(descriptorSetLayout.size());
        createInfo.pSetLayouts = descriptorSetLayout.data();
        createInfo.pushConstantRangeCount = static_cast<u32>(pushConstantRanges.size());
        createInfo.pPushConstantRanges = pushConstantRanges.data();

        if (vkCreatePipelineLayout(device, &createInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            std::string msg = "VulkanPipelineLayoutUtil::Create: failed to create pipeline layout";
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return pipelineLayout;
    }

    VkPipelineLayout VulkanPipelineLayoutUtil::Create(VkDevice device,
                                                      const std::vector<VkDescriptorSetLayout> &descriptorSetLayouts)
    {
        std::vector<VkPushConstantRange> emptyPushConstantRange;
        return Create(device, descriptorSetLayouts, emptyPushConstantRange);
    }

    void VulkanPipelineLayoutUtil::Destroy(VkDevice device, VkPipelineLayout pipelineLayout)
    {
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    }

} // namespace bns

#endif