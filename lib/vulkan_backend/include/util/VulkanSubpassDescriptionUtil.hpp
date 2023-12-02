#pragma once

#if USE_VULKAN

#ifndef BNS_VULKAN_SUBPASS_DESCRIPTION_UTIL_HPP

#define BNS_VULKAN_SUBPASS_DESCRIPTION_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>

namespace bns
{
    /// @brief Utility class for creating @ref VkSubpassDescription.
    struct VulkanSubpassDescriptionUtil
    {
        /// @brief Creates a default @ref VkSubpassDescription.
        /// @param colorAttachmentRefs The @ref VkAttachmentReference to use for color attachments.
        /// @param depthAttachmentRef The @ref VkAttachmentReference to use for depth attachments.
        /// @return The default @ref VkSubpassDescription.
        static VkSubpassDescription Create(const std::vector<VkAttachmentReference> &colorAttachmentRefs, const VkAttachmentReference &depthAttachmentRef);

        /// @brief Creates a default @ref VkSubpassDescription.
        /// @param colorAttachmentRefs The @ref VkAttachmentReference to use for color attachments.
        /// @return The default @ref VkSubpassDescription.
        static VkSubpassDescription Create(const std::vector<VkAttachmentReference> &colorAttachmentRefs);

        /// @brief Creates a default @ref VkSubpassDescription.
        /// @param colorAttachmentRef The @ref VkAttachmentReference to use for color attachment.
        /// @return The default @ref VkSubpassDescription.
        static VkSubpassDescription Create(const VkAttachmentReference &colorAttachmentRef);
    };
} // namespace bns

#endif

#endif