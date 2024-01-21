#if USE_VULKAN

#ifndef BNS_VULKAN_DESCRIPTOR_POOL_UTIL_HPP

#define BNS_VULKAN_DESCRIPTOR_POOL_UTIL_HPP

#include "BnsVulkan.hpp"
#include "Types.hpp"

namespace bns
{
    struct VulkanDescriptorPoolUtil
    {
        /// @brief Creates a @ref VkDescriptorPool
        /// @param device The device to create the descriptor pool on
        /// @param poolSizeType The type of descriptor pool size. Usually @ref VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER
        /// @param poolSizeDescriptorCount The descriptor count for the pool size. Usually should correspond to frames in flight
        /// @param maxSets The max sets for the descriptor pool. Usually should correspond to frames in flight
        /// @return The created descriptor pool.
        static VkDescriptorPool Create(const VkDevice &device, VkDescriptorType poolSizeType, u32 poolSizeDescriptorCount, u32 maxSets);

        /// @brief Creates a @ref VkDescriptorPool for uniform buffers
        /// @param device The device to create the descriptor pool on
        /// @param frameInFlightCount The frame in flight count. This is used for the descriptor count and max sets.
        /// @return The created descriptor pool.
        static VkDescriptorPool CreateForUniformBuffer(const VkDevice &device, u32 frameInFlightCount = 1);
    };
}

#endif 

#endif