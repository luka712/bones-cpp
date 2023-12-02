#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_DYNAMIC_STATE_CREATE_INFO_HPP

#define BNS_VULKAN_PIPELINE_DYNAMIC_STATE_CREATE_INFO_HPP

#include "BnsVulkan.hpp"
#include <vector>

namespace bns
{
    /// @brief The util class for working with @ref VkPipelineDynamicStateCreateInfo
    struct VulkanPipelineDynamicStateCreateInfoUtil
    {
        /// @brief Get the default dynamic states used by the application.
        /// @return The default dynamic states. @ref VK_DYNAMIC_STATE_VIEWPORT and @ref VK_DYNAMIC_STATE_SCISSOR.
        inline static std::vector<VkDynamicState> DefaultDynamicStates() 
        {
            return {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
        }

        /// @brief Creates a @ref VkPipelineDynamicStateCreateInfo with the given dynamicStates.
        /// @param dynamicStates The dynamic states to use.
        /// @return The created @ref VkPipelineDynamicStateCreateInfo.
        static VkPipelineDynamicStateCreateInfo Create(const std::vector<VkDynamicState> &dynamicStates);
    };
} // namespace bns

#endif

#endif