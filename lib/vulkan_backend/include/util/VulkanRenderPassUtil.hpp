#if USE_VULKAN

#ifndef BNS_VULKAN_RENDER_PASS_UTIL_HPP

#define BNS_VULKAN_RENDER_PASS_UTIL_HPP

// Vulkan
#include "BnsVulkan.hpp"
#include <vector>

namespace bns
{
    struct VulkanRenderPassUtil
    {
        /// @brief Create a @ref VkRenderPass
        /// @param device The @ref VkDevice
        /// @param attachmentDescriptions The @ref VkAttachmentDescription array
        /// @param subpassDescriptions The @ref VkSubpassDescription array
        /// @return 
        static VkRenderPass Create(const VkDevice &device,
                                   const std::vector<VkAttachmentDescription> &attachmentDescriptions,
                                   const std::vector<VkSubpassDescription> &subpassDescriptions);

        /// @brief Destroy a @ref VkRenderPass
        /// @param device The @ref VkDevice
        /// @param renderPass The @ref VkRenderPass
        static void Destroy(const VkDevice &device,
                            const VkRenderPass &renderPass);
    };
}

#endif

#endif