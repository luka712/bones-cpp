#if USE_VULKAN

#include "util/VulkanDescriptorPoolUtil.hpp"
#include <stdexcept>
#include <string>

namespace bns
{
    VkDescriptorPool VulkanDescriptorPoolUtil::Create(const VkDevice &device, VkDescriptorType poolSizeType, u32 poolSizeDescriptorCount, u32 maxSets)
    {
        // We first need to describe which descriptor types our descriptor sets are going to contain
        // and how many of them, using VkDescriptorPoolSize structures.
        VkDescriptorPoolSize poolSize;
        poolSize.type = poolSizeType;
        poolSize.descriptorCount = poolSizeDescriptorCount; // usually should correspond to frames in flight

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;
        poolInfo.maxSets = maxSets; // usually should correspond to frames in flight

        VkDescriptorPool descriptorPool;
        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
        {
            std::string msg = "VulkanDescriptorPoolUtil::Create: failed to create descriptor pool!";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return descriptorPool;
    }

    VkDescriptorPool VulkanDescriptorPoolUtil::CreateForUniformBuffer(const VkDevice &device, u32 frameInFlightCount)
    {
        return Create(device, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, frameInFlightCount, frameInFlightCount);
    }
}

#endif