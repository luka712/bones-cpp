#if USE_VULKAN

#include "util/VulkanAttachmentDescriptionUtil.hpp"

namespace bns
{
    VkAttachmentDescription VulkanAttachmentDescriptionUtil::CreateColorAttachment(VkFormat format)
    {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = format;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;   // Clear the framebuffer before rendering.
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE; // Store the result of the fragment shader in the framebuffer.
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        // We don't care about the initial layout of the attachment, because we're going to clear it anyway.
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        // After rendering, the image has to be transformed to a layout that is ready for presentation using a swap chain.
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        return colorAttachment;
    }
} // namespace bns

#endif 