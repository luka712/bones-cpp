#if USE_VULKAN

#ifndef BNS_VULKAN_DESCRIPTOR_SET_UTIL_HPP

#define BNS_VULKAN_DESCRIPTOR_SET_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>
#include "Types.hpp"

namespace bns
{
    struct VulkanDescriptorSetUtil
    {
        /// @brief Creates a @ref VkDescriptorSet
        /// @param device The device to create the descriptor set on
        /// @param descriptorPool The descriptor pool to create the descriptor set on
        /// @param descriptorSetLayouts The descriptor set layouts to create the descriptor set on
        /// @param maxFramesInFlight The max frames in flight
        /// @return The created descriptor sets
        static std::vector<VkDescriptorSet> Create(
            const VkDevice &device,
            const VkDescriptorPool &descriptorPool,
            const std::vector<VkDescriptorSetLayout> &descriptorSetLayouts,
            u32 maxFramesInFlight);

        /// @brief Updates a @ref VkDescriptorSet
        /// @param device The device to update the descriptor set on
        /// @param descriptorSet The descriptor set to update
        /// @param binding The binding to update. This is the binding in the shader. In glsl it's set as layout(binding = {binding})
        /// @param buffer The buffer to update the descriptor set with
        /// @param bufferSize The size of the buffer
        /// @param bufferOffset The offset into the buffer
        static void UpdateUniform(
            const VkDevice &device,
            const VkDescriptorSet &descriptorSet,
            u32 binding, 
            const VkBuffer &buffer,
            size_t bufferSize,
            u32 bufferOffset = 0);
    };
}

#endif

#endif