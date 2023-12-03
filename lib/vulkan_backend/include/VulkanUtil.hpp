#if USE_VULKAN

#ifndef BNS_VULKAN_UTIL_HPP

#define BNS_VULKAN_UTIL_HPP

#include "util/VulkanAttachmentDescriptionUtil.hpp"
#include "util/vulkanAttachmentReferenceUtil.hpp"
#include "util/VulkanSubpassDescriptionUtil.hpp"
#include "util/VulkanRenderPassUtil.hpp"
#include "util/VulkanFramebufferUtil.hpp"
#include "util/VulkanCommandPoolUtil.hpp"
#include "util/VulkanCommandBufferUtil.hpp"
#include "util/VulkanCommandBufferBeginInfoUtil.hpp"
#include "util/VulkanRenderPassBeginInfoUtil.hpp"
#include "util/VulkanVIewportUtil.hpp"
#include "util/VulkanSemaphoreUtil.hpp"
#include "util/VulkanFenceUtil.hpp"
#include "util/VulkanSubmitInfoUtil.hpp"

namespace bns 
{
    struct VulkanUtil 
    {
        /// @brief The @ref VulkanAttachmentDescriptionUtil for working with @ref VkAttachmentDescription
        static VulkanAttachmentDescriptionUtil AttachmentDescription;

        /// @brief The @ref VulkanAttachmentReferenceUtil for working with @ref VkAttachmentReference
        static VulkanAttachmentReferenceUtil AttachmentReference;

        /// @brief The @ref VulkanCommandBufferUtil for working with @ref VkCommandBuffer
        static VulkanCommandBufferUtil CommandBuffer;

        /// @brief The @ref VulkanCommandBufferBeginInfoUtil for working with @ref VkCommandBufferBeginInfo
        static VulkanCommandBufferBeginInfoUtil CommandBufferBeginInfo;

        /// @brief The @ref VulkanCommandPoolUtil for working with @ref VkCommandPool
        static VulkanCommandPoolUtil CommandPool;

        /// @brief The @ref VulkanFenceUtil for working with @ref VkFence
        static VulkanFenceUtil Fence;

        /// @brief The @ref VulkanFramebufferUtil for working with @ref VkFramebuffer
        static VulkanFramebufferUtil Framebuffer;

        /// @brief The @ref VulkanSemaphoreUtil for working with @ref VkSemaphore
        static VulkanSemaphoreUtil Semaphore;

        /// @brief The @ref VulkanSubmitInfoUtil for working with @ref VkSubmitInfo
        static VulkanSubmitInfoUtil SubmitInfo;

        /// @brief The @ref VulkanSubpassDescriptionUtil for working with @ref VkSubpassDescription
        static VulkanSubpassDescriptionUtil SubpassDescription;

        /// @brief The @ref VulkanRenderPassUtil for working with @ref VkRenderPass
        static VulkanRenderPassUtil RenderPass;

        /// @brief The @ref VulkanRenderPassBeginInfoUtil for working with @ref VkRenderPassBeginInfo
        static VulkanRenderPassBeginInfoUtil RenderPassBeginInfo;

        /// @brief The @ref VulkanViewportUtil for working with @ref VkViewport
        static VulkanViewportUtil Viewport;
    };
}

#endif 

#endif 