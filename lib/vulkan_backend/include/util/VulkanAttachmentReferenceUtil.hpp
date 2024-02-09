#pragma once

#if USE_VULKAN

#ifndef BNS_VULKAN_ATTACHMENT_REFERENCE_UTIL_HPP

#define BNS_VULKAN_ATTACHMENT_REFERENCE_UTIL_HPP

#include "bns_types.hpp"
#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkAttachmentReference.
    struct VulkanAttachmentReferenceUtil
    {
        /// @brief Creates a default @ref VkAttachmentReference for a color attachment.
        /// @param attachmentLocation The attachment location to use. Usually in glsl this is the location of the output variable. 
        /// For example in "layout(location = 0) out vec4 outColor;" it would be 0.
        /// @return The default @ref VkAttachmentReference for a color attachment.
        static VkAttachmentReference CreateColorAttachmentRef(u32 attachmentLocation = 0);
    };
} // namespace bns

#endif

#endif