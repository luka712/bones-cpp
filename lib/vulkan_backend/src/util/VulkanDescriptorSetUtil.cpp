#if USE_VULKAN

#include "util/VulkanDescriptorSetUtil.hpp"
#include <string>
#include <stdexcept>

namespace bns
{

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
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return descriptorSets;
    }

    /// @brief Updates a @ref VkDescriptorSet
    /// @param device The device to update the descriptor set on
    /// @param descriptorSet The descriptor set to update
    /// @param binding The binding to update. This is the binding in the shader. In glsl it's set as layout(binding = {binding})
    /// @param buffer The buffer to update the descriptor set with
    /// @param bufferSize The size of the buffer
    /// @param bufferOffset The offset into the buffer
     void VulkanDescriptorSetUtil::UpdateUniform(
        const VkDevice &device,
        const VkDescriptorSet &descriptorSet,
        u32 binding,
        const VkBuffer &buffer,
        size_t bufferSize,
        u32 bufferOffset )
    {
        // https://vkguide.dev/docs/chapter-4/descriptors/
        // Prepare the buffer info. This is sorf of pointer to a buffer.
        VkDescriptorBufferInfo bufferInfo = {};
        bufferInfo.buffer = buffer;       // Buffer to get data from
        bufferInfo.offset = bufferOffset; // Offset into the buffer
        bufferInfo.range = bufferSize;    // Size of the buffer data (starting at offset)

        VkWriteDescriptorSet writeDescriptorSet = {};
        writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeDescriptorSet.dstSet = descriptorSet;
        writeDescriptorSet.dstBinding = binding; // The binding in the shader
        writeDescriptorSet.dstArrayElement = 0;
        writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        writeDescriptorSet.descriptorCount = 1;
        writeDescriptorSet.pBufferInfo = &bufferInfo;
        writeDescriptorSet.pImageInfo = nullptr;
        writeDescriptorSet.pTexelBufferView = nullptr;

        vkUpdateDescriptorSets(device, 1, &writeDescriptorSet, 0, nullptr);
    }
}

#endif