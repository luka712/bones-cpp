#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO_UTIL_HPP

#define BNS_VULKAN_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>

namespace bns
{
    /// @brief Utility class for creating @ref VkPipelineVertexInputStateCreateInfo structs
    struct VulkanPipelineVertexInputStateCreateInfoUtil final
    {
        /// @brief Creates a @ref VkPipelineVertexInputStateCreateInfo
        /// @param vertexInputBindingDescriptions The vertex input binding descriptions.
        /// @param vertexInputAttributeDescriptions The vertex input attribute descriptions.
        /// @return The created @ref VkPipelineVertexInputStateCreateInfo
        static VkPipelineVertexInputStateCreateInfo Create(
            const std::vector<VkVertexInputBindingDescription> &vertexInputBindingDescriptions,
            const std::vector<VkVertexInputAttributeDescription> &vertexInputAttributeDescriptions);
    };
}

#endif // !BNS_VULKAN_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO_UTIL_HPP

#endif