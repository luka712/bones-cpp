#if USE_VULKAN

#ifndef BNS_VULKAN_DESCRIPTOR_SET_LAYOUT_UTIL_HPP

#define BNS_VULKAN_DESCRIPTOR_SET_LAYOUT_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>

namespace bns
{
    struct VulkanDescriptorSetLayoutUtil
    {
        /// @brief The @ref VkDescriptorSetLayoutBinding for working with @ref VkDescriptorSetLayoutBinding
        /// @param device The device to create the descriptor set layout for.
        /// @param binding The binding to create the descriptor set layout with.
        /// @return The created @ref VkDescriptorSetLayout
        static VkDescriptorSetLayout Create(const VkDevice &device, const VkDescriptorSetLayoutBinding &binding);

        /// @brief Creates a @ref VkDescriptorSetLayout
        /// @param device The device to create the descriptor set layout for.
        /// @param bindings The bindings to create the descriptor set layout with.
        /// @return The created @ref VkDescriptorSetLayout
        static VkDescriptorSetLayout Create(const VkDevice &device, const std::vector<VkDescriptorSetLayoutBinding> &bindings);

        /// @brief Destroys a @ref VkDescriptorSetLayout
        /// @param device The device to destroy the descriptor set layout for.
        /// @param descriptorSetLayout The descriptor set layout to destroy.
        static void Destroy(const VkDevice &device, const VkDescriptorSetLayout &descriptorSetLayout);
    };
}

#endif

#endif