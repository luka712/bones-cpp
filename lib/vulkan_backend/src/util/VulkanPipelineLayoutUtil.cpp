#if USE_VULKAN

#include "util/VulkanPipelineLayoutUtil.hpp"
#include "Types.hpp"
#include <string>
#include <stdexcept>

namespace bns
{
    VkPipelineLayout VulkanPipelineLayoutUtil::Create(VkDevice device,  const std::vector<VkDescriptorSetLayout> &descriptorSetLayout)
    {
        VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;

        VkPipelineLayoutCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        createInfo.setLayoutCount = static_cast<u32>(descriptorSetLayout.size());
        createInfo.pSetLayouts = descriptorSetLayout.data();
        createInfo.pushConstantRangeCount = 0; // Optional
        createInfo.pPushConstantRanges = nullptr; // Optional

        if(vkCreatePipelineLayout(device, &createInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            std::string msg = "VulkanPipelineLayoutUtil::Create: failed to create pipeline layout";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return pipelineLayout;
    }

    void VulkanPipelineLayoutUtil::Destroy(VkDevice device, VkPipelineLayout pipelineLayout)
    {
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    }

} // namespace bns

#endif 