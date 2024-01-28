#if USE_VULKAN

#include "util/VulkanDescriptorPoolUtil.hpp"
#include <stdexcept>
#include <string>

namespace bns
{
    VkDescriptorPool VulkanDescriptorPoolUtil::Create(const VkDevice &device, const std::vector<VkDescriptorPoolSize> &poolSizes, u32 poolSizeDescriptorCount, u32 maxSets)
    {
        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<u32>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = maxSets; // usually should correspond to frames in flight

        VkDescriptorPool descriptorPool;
        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
        {
            std::string msg = "VulkanDescriptorPoolUtil::Create: failed to create descriptor pool!";
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return descriptorPool;
    }

    VkDescriptorPool VulkanDescriptorPoolUtil::Create(const VkDevice &device, std::vector<VkDescriptorType> types, u32 frameInFlightCount)
    {
        std::vector<VkDescriptorPoolSize> poolSize = std::vector<VkDescriptorPoolSize>(types.size());
        for (u32 i = 0; i < types.size(); i++)
        {
            poolSize[i].type = types[i];
            poolSize[i].descriptorCount = frameInFlightCount;
        }

        return Create(device, poolSize, frameInFlightCount, frameInFlightCount);
    }

    VkDescriptorPool VulkanDescriptorPoolUtil::CreateForUniformBuffer(const VkDevice &device, u32 frameInFlightCount)
    {
        std::vector<VkDescriptorPoolSize> poolSize = std::vector<VkDescriptorPoolSize>(1);
        poolSize[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize[0].descriptorCount = frameInFlightCount;

        return Create(device, poolSize, frameInFlightCount, frameInFlightCount);
    }
}

#endif