#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO_UTIL_HPP

#define BNS_VULKAN_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO_UTIL_HPP

#include <vulkan/vulkan.h>

namespace bns
{
    /// @brief Utility class for creating @ref VkPipelineMultisampleStateCreateInfo.
    struct VulkanPipelineMultisampleStateCreateInfoUtil
    {
        /// @brief Creates a default @ref VkPipelineMultisampleStateCreateInfo. By default no multisampling.
        /// @return The default @ref VkPipelineMultisampleStateCreateInfo.
        static VkPipelineMultisampleStateCreateInfo Create();
    };
} // namespace bns

#endif 

#endif 