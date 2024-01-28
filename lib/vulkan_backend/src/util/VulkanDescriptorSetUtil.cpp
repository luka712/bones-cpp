#if USE_VULKAN

#include "util/VulkanDescriptorSetUtil.hpp"
#include <string>
#include <stdexcept>

namespace bns
{
    VulkanUpdateDescriptorDto::VulkanUpdateDescriptorDto(
        u32 binding,
        VkDescriptorType descriptorType,
        VkDescriptorBufferInfo *bufferInfo,
        VkDescriptorImageInfo *imageInfo) : Binding(binding), DescriptorType(descriptorType), BufferInfo(bufferInfo), ImageInfo(imageInfo)
    {
    }

    std::vector<VkDescriptorSet> VulkanDescriptorSetUtil::Create(
        const VkDevice &device,
        const VkDescriptorPool &descriptorPool,
        const std::vector<VkDescriptorSetLayout> &descriptorSetLayouts,
        u32 maxFramesInFlight)
    {
        VkDescriptorSetAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<u32>(descriptorSetLayouts.size());
        allocInfo.pSetLayouts = descriptorSetLayouts.data();

        std::vector<VkDescriptorSet> descriptorSets(maxFramesInFlight);
        if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
        {
            std::string msg = "VulkanDescriptorSetUtil::Create: Failed to allocate descriptor sets";
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return descriptorSets;
    }

    void VulkanDescriptorSetUtil::Update(
        const VkDevice &device,
        const VkDescriptorSet &descriptorSet,
        const std::vector<VulkanUpdateDescriptorDto> &dtos)
    {
        std::vector<VkWriteDescriptorSet> writeDescriptorSets(dtos.size());
        for (size_t i = 0; i < dtos.size(); i++)
        {
            const VulkanUpdateDescriptorDto &dto = dtos[i];

            VkWriteDescriptorSet& writeDescriptorSet = writeDescriptorSets[i];
            writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            writeDescriptorSet.dstSet = descriptorSet;
            writeDescriptorSet.dstBinding = dto.Binding; // The binding in the shader. layout(binding = {binding}) 
            writeDescriptorSet.dstArrayElement = 0;
            writeDescriptorSet.descriptorType = dto.DescriptorType; // usually VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER or VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
            writeDescriptorSet.descriptorCount = 1;
            writeDescriptorSet.pBufferInfo = dto.BufferInfo;
            writeDescriptorSet.pImageInfo = dto.ImageInfo;
            writeDescriptorSet.pTexelBufferView = nullptr;
        }

        vkUpdateDescriptorSets(device, writeDescriptorSets.size(), writeDescriptorSets.data(), 0, nullptr);
    }
}

#endif