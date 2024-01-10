#if USE_VULKAN 

#ifndef BNS_VULKAN_PUSH_CONSTANT_RANGE_UTIL_HPP

#define BNS_VULKAN_PUSH_CONSTANT_RANGE_UTIL_HPP

#include "Types.hpp"
#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkPushConstantRange structs.
    struct VulkanPushConstantRangeUtil final
    {
        /// @brief Creates a @ref VkPushConstantRange struct.
        /// @param stageFlags The stage flags.
        /// @param offset The offset.
        /// @param size The size.
        /// @return The created @ref VkPushConstantRange struct.
        static VkPushConstantRange Create(VkShaderStageFlags stageFlags, u32 offset, u32 size);
    };
} // namespace bns

#endif 

#endif 