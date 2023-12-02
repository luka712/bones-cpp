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
        static VkPipelineInputAssemblyStateCreateInfo Default();
    };
} // namespace bns

#endif // !BNS_VULKAN_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO_UTIL_HPP

#endif