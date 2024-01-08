#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO_UTIL_HPP

#define BNS_VULKAN_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief The util class for working with @ref VkPipelineInputAssemblyStateCreateInfo
    struct VulkanPipelineInputAssemblyStateCreateInfoUtil final
    {
        /// @brief Get the default @ref VkPipelineInputAssemblyStateCreateInfo.
        /// @return The default @ref VkPipelineInputAssemblyStateCreateInfo.
        /// @note The default topology is @ref VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST.
        static VkPipelineInputAssemblyStateCreateInfo Default();

        /// @brief Create a @ref VkPipelineInputAssemblyStateCreateInfo with the @ref VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST topology.
        /// @return The @ref VkPipelineInputAssemblyStateCreateInfo with the @ref VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST topology.
        static VkPipelineInputAssemblyStateCreateInfo CreateWithTriangleListTopology();
    };
} // namespace bns

#endif // !BNS_VULKAN_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO_UTIL_HPP

#endif