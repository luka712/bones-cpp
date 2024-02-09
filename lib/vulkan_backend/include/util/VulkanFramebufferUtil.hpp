#if USE_VULKAN

#ifndef __UTIL_VULKAN_FRAMEBUFFER_UTIL_HPP__
#define __UTIL_VULKAN_FRAMEBUFFER_UTIL_HPP__

#include "BnsVulkan.hpp"
#include "bns_types.hpp"
#include <vector>

namespace bns
{
    /// @brief A utility class for creating and destroying @ref VkFramebuffer
    struct VulkanFramebufferUtil
    {
        /// @brief Creates a framebuffer for the given image view and render pass
        /// @param device The device to create the framebuffer on
        /// @param renderPass The render pass to create the framebuffer for
        /// @param imageView The image view to create the framebuffer for
        /// @param swapChainExtent The extent of the swap chain
        /// @return The created @ref VkFramebuffer
        static VkFramebuffer Create(VkDevice device, VkRenderPass renderPass, VkImageView imageView, VkExtent2D swapChainExtent);

        /// @brief Creates a framebuffers for the given image views and render pass
        /// @param device The device to create the framebuffers on
        /// @param renderPass The render pass to create the framebuffers for
        /// @param imageViews The image views to create the framebuffers for
        /// @param swapChainExtent The extent of the swap chain
        /// @return The created @ref VkFramebuffer
        static std::vector<VkFramebuffer> Create(VkDevice device, VkRenderPass renderPass, std::vector<VkImageView> imageViews, VkExtent2D swapChainExtent);

        /// @brief The function to destroy a framebuffer
        /// @param device The device to destroy the framebuffer on
        /// @param framebuffer The framebuffer to destroy
        static void Destroy(VkDevice device, VkFramebuffer framebuffer);
    };

}

#endif // __UTIL_VULKAN_FRAMEBUFFER_UTIL_HPP__

#endif