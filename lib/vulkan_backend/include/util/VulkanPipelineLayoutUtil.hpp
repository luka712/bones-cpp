#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_LAYOUT_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>

namespace bns
{
    /// @brief Utility class for creating @ref VkPipelineLayoutCreateInfo.
    struct VulkanPipelineLayoutUtil
    {
        /// @brief Creates a default @ref VkPipelineLayoutCreateInfo.
        /// @param device The @ref VkDevice to use.
        /// @param descriptorSetLayout The @ref VkDescriptorSetLayout to use.
        /// @param pushConstantRanges The @ref VkPushConstantRange to use.
        /// @return The default @ref VkPipelineLayoutCreateInfo.
        static VkPipelineLayout Create(VkDevice device,
                                       const std::vector<VkDescriptorSetLayout> &descriptorSetLayout,
                                       const std::vector<VkPushConstantRange> &pushConstantRanges);

        /// @brief Creates a default @ref VkPipelineLayoutCreateInfo.
        /// @param device The @ref VkDevice to use.
        /// @param descriptorSetLayout The @ref VkDescriptorSetLayout to use.
        /// @return The default @ref VkPipelineLayoutCreateInfo.
        static VkPipelineLayout Create(VkDevice device,
                                       const std::vector<VkDescriptorSetLayout> &descriptorSetLayout);

        /// @brief Destroys a @ref VkPipelineLayout.
        /// @param device The @ref VkDevice to use.
        /// @param pipelineLayout The @ref VkPipelineLayout to destroy.
        static void Destroy(VkDevice device, VkPipelineLayout pipelineLayout);
    };
} // namespace bns

#endif

#endif