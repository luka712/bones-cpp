#if USE_VULKAN

#ifndef BNS_VULKAN_RENDER_PASS_BEGIN_INFO_HPP

#define BNS_VULKAN_RENDER_PASS_BEGIN_INFO_HPP

#include "BnsVulkan.hpp"
#include "bns_types.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkRenderPassBeginInfo
    struct VulkanRenderPassBeginInfoUtil
    {
        /// @brief Creates a @ref VkRenderPassBeginInfo
        /// @param renderPass The render pass.
        /// @param framebuffer The framebuffer.
        /// @param swapChainExtent The swap chain extent.
        /// @param clearColor The clear values.
        /// @return The created @ref VkRenderPassBeginInfo
        static VkRenderPassBeginInfo Create(VkRenderPass renderPass, 
                                            VkFramebuffer framebuffer, 
                                            VkExtent2D swapChainExtent, 
                                            const VkClearValue& clearColor);
    };
} // namespace bns

#endif 

#endif