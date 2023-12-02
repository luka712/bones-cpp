#pragma once

#if USE_VULKAN

#ifndef BNS_VULKAN_ATTACHMENT_DESCRIPTION_UTIL_HPP

#define BNS_VULKAN_ATTACHMENT_DESCRIPTION_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkAttachmentDescription.
    struct VulkanAttachmentDescriptionUtil
    {
        /// @brief Creates a default @ref VkAttachmentDescription.
        /// @param format The @ref VkFormat to use. By default @ref VK_FORMAT_B8G8R8A8_UNORM.
        /// @return The default @ref VkAttachmentDescription.
        static VkAttachmentDescription CreateColorAttachment(VkFormat format = VK_FORMAT_B8G8R8A8_UNORM);
    };
} // namespace bns

#endif

#endif