#if USE_VULKAN

#ifndef BNS_VULKAN_UTIL_HPP

#define BNS_VULKAN_UTIL_HPP

#include "util/VulkanAttachmentDescriptionUtil.hpp"
#include "util/vulkanAttachmentReferenceUtil.hpp"
#include "util/VulkanSubpassDescriptionUtil.hpp"
#include "util/VulkanRenderPassUtil.hpp"

namespace bns 
{
    struct VulkanUtil 
    {
        /// @brief The @ref VulkanAttachmentDescriptionUtil for working with @ref VkAttachmentDescription
        static VulkanAttachmentDescriptionUtil AttachmentDescription;

        /// @brief The @ref VulkanAttachmentReferenceUtil for working with @ref VkAttachmentReference
        static VulkanAttachmentReferenceUtil AttachmentReference;

        /// @brief The @ref VulkanSubpassDescriptionUtil for working with @ref VkSubpassDescription
        static VulkanSubpassDescriptionUtil SubpassDescription;

        /// @brief The @ref VulkanRenderPassUtil for working with @ref VkRenderPass
        static VulkanRenderPassUtil RenderPass;
    };
}

#endif 

#endif 