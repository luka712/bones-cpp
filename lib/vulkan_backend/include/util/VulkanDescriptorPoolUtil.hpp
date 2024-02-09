#if USE_VULKAN

#ifndef BNS_VULKAN_DESCRIPTOR_POOL_UTIL_HPP

#define BNS_VULKAN_DESCRIPTOR_POOL_UTIL_HPP

#include "BnsVulkan.hpp"
#include "bns_types.hpp"
#include <vector>

namespace bns
{
    struct VulkanDescriptorPoolUtil
    {
        /// @brief Creates a @ref VkDescriptorPool
        /// @param device The device to create the descriptor pool on
        /// @param poolSizes The pool sizes for the descriptor pool
        /// @param poolSizeDescriptorCount The descriptor count for the pool size. Usually should correspond to frames in flight
        /// @param maxSets The max sets for the descriptor pool. Usually should correspond to frames in flight
        /// @return The created descriptor pool.
        static VkDescriptorPool Create(const VkDevice &device, const std::vector<VkDescriptorPoolSize> &poolSizes, u32 poolSizeDescriptorCount, u32 maxSets);

        /// @brief Creates a @ref VkDescriptorPool
        /// @param device The device to create the descriptor pool on
        /// @param types The descriptor types for the descriptor pool
        /// @param frameInFlightCount The frame in flight count.
        /// @return The created descriptor pool.
        static VkDescriptorPool Create(const VkDevice &device, std::vector<VkDescriptorType> types, u32 frameInFlightCount = 1);

        /// @brief Creates a @ref VkDescriptorPool for uniform buffers
        /// @param device The device to create the descriptor pool on
        /// @param frameInFlightCount The frame in flight count. This is used for the descriptor count and max sets.
        /// @return The created descriptor pool.
        static VkDescriptorPool CreateForUniformBuffer(const VkDevice &device, u32 frameInFlightCount = 1);
    };
}

#endif

#endif