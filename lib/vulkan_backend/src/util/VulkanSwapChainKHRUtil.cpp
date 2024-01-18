#if USE_VULKAN

#include "util/VulkanSwapChainKHRUtil.hpp"
#include <string>
#include <stdexcept>
#include <algorithm>
#include "VulkanUtil.hpp"

namespace bns
{
    void VulkanSwapChainKHRUtil::LogTransformBits(VkSurfaceTransformFlagsKHR transformBits)
    {
        LOG("Surface transform bits:");
        LOG("Identity: %d", transformBits & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR);
        LOG("Rotate 90: %d", transformBits & VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR);
        LOG("Rotate 180: %d", transformBits & VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR);
        LOG("Rotate 270: %d", transformBits & VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR);
        LOG("Horizontal mirror: %d", transformBits & VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR);
        LOG("Horizontal mirror rotate 90: %d", transformBits & VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR);
        LOG("Horizontal mirror rotate 180: %d", transformBits & VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR);
        LOG("Horizontal mirror rotate 270: %d", transformBits & VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR);
        LOG("Inherit: %d", transformBits & VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR);
    }

    void VulkanSwapChainKHRUtil::LogAlphaCompositeBits(VkCompositeAlphaFlagsKHR alphaCompositeBits)
    {
        LOG("Alpha composite bits:");
        LOG("Opaque: %d", alphaCompositeBits & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR);
        LOG("Pre-multiplied: %d", alphaCompositeBits & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR);
        LOG("Post-multiplied: %d", alphaCompositeBits & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR);
        LOG("Inherit: %d", alphaCompositeBits & VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR);
    }

    void VulkanSwapChainKHRUtil::LogSupportedImageUses(VkImageUsageFlags supportedImageUses)
    {
        LOG("Supported image uses:");
        LOG("Transfer source: %d", supportedImageUses & VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
        LOG("Transfer destination: %d", supportedImageUses & VK_IMAGE_USAGE_TRANSFER_DST_BIT);
        LOG("Sampled: %d", supportedImageUses & VK_IMAGE_USAGE_SAMPLED_BIT);
        LOG("Storage: %d", supportedImageUses & VK_IMAGE_USAGE_STORAGE_BIT);
        LOG("Color attachment: %d", supportedImageUses & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);
        LOG("Depth stencil attachment: %d", supportedImageUses & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);
        LOG("Transient attachment: %d", supportedImageUses & VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT);
        LOG("Input attachment: %d", supportedImageUses & VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT);
    }

    void VulkanSwapChainKHRUtil::LogSurfaceCapabilities(VkSurfaceCapabilitiesKHR surfaceCapabilities)
    {
        LOG("Surface capabilities:");
        LOG("Min image count: %d", surfaceCapabilities.minImageCount);
        LOG("Max image count: %d", surfaceCapabilities.maxImageCount);
        LOG("Current extent: %d x %d", surfaceCapabilities.currentExtent.width, surfaceCapabilities.currentExtent.height);
        LOG("Min image extent: %d x %d", surfaceCapabilities.minImageExtent.width, surfaceCapabilities.minImageExtent.height);
        LOG("Max image extent: %d x %d", surfaceCapabilities.maxImageExtent.width, surfaceCapabilities.maxImageExtent.height);
        LOG("Max image array layers: %d", surfaceCapabilities.maxImageArrayLayers);
        LOG("Supported transforms: %d", surfaceCapabilities.supportedTransforms);
        LOG("Current transform: %d", surfaceCapabilities.currentTransform);
    }

    VkSurfaceFormatKHR VulkanSwapChainKHRUtil::ChooseSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR> &availableFormats)
    {

        // Try to find the preferred format.
        for (const VkSurfaceFormatKHR &availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
                availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return availableFormat;
            }
        }

        // If we can't find the preferred format, then we just choose the first available format.
        return availableFormats[0];
    }

    VkPresentModeKHR VulkanSwapChainKHRUtil::ChoosePresentMode(
        const std::vector<VkPresentModeKHR> &availablePresentModes)
    {
        // Try to find the preferred present mode.
        for (const VkPresentModeKHR &availablePresentMode : availablePresentModes)
        {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                return availablePresentMode;
            }
        }

        // If we can't find the preferred present mode, then we just choose the first available present mode.
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanSwapChainKHRUtil::ChooseExtent(
        const VkSurfaceCapabilitiesKHR &surfaceCapabilities,
        u32 width,
        u32 height)
    {
        // Otherwise, we need to choose the extent.
        VkExtent2D actualExtent = {width, height};

        // Clamp the width.
        actualExtent.width = std::max(
            surfaceCapabilities.minImageExtent.width,
            std::min(surfaceCapabilities.maxImageExtent.width, actualExtent.width));

        // Clamp the height.
        actualExtent.height = std::max(
            surfaceCapabilities.minImageExtent.height,
            std::min(surfaceCapabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }

    void VulkanSwapChainKHRUtil::QuerySwapChainSupport(
        VkPhysicalDevice device,
        VkSurfaceKHR surface,
        VkSurfaceCapabilitiesKHR *outSurfaceCapabilities,
        std::vector<VkSurfaceFormatKHR> *outFormats,
        std::vector<VkPresentModeKHR> *outPresentModes)
    {
        // Get the surface capabilities.
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, outSurfaceCapabilities);

// Log capabilities.
#if DEBUG
        LogSurfaceCapabilities(*outSurfaceCapabilities);
        LOG("Supported transforms bits:");
        LogTransformBits(outSurfaceCapabilities->supportedTransforms);
        LOG("Current transform bits:");
        LogTransformBits(outSurfaceCapabilities->currentTransform);
        LogAlphaCompositeBits(outSurfaceCapabilities->supportedCompositeAlpha);
        LogSupportedImageUses(outSurfaceCapabilities->supportedUsageFlags);
#endif

        u32 formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        // Resize the out formats.
        outFormats->resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, outFormats->data());

        u32 presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        // Resize the out present modes.
        outPresentModes->resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, outPresentModes->data());
    }

    VkSwapchainKHR VulkanSwapChainKHRUtil::Create(VkPhysicalDevice physicalDevice,
                                                  VkDevice device,
                                                  VkSurfaceKHR surface,
                                                  u32 width, u32 height,
                                                  std::vector<VkImage> *outImages,
                                                  VkFormat *outFormat,
                                                  VkExtent2D *outExtent)
    {
        // Query the swap chain support.
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        std::vector<VkSurfaceFormatKHR> surfaceFormats;
        std::vector<VkPresentModeKHR> presentModes;

        QuerySwapChainSupport(
            physicalDevice,
            surface,
            &surfaceCapabilities,
            &surfaceFormats,
            &presentModes);

        // Choose the surface format.
        VkSurfaceFormatKHR surfaceFormat = ChooseSurfaceFormat(surfaceFormats);

        // Choose the present mode.
        VkPresentModeKHR presentMode = ChoosePresentMode(presentModes);

        // Choose the extent.
        VkExtent2D extent = ChooseExtent(surfaceCapabilities, width, height);

        // Get the image count.
        uint32_t imageCount = std::min(surfaceCapabilities.minImageCount + 1, surfaceCapabilities.maxImageCount);

        // Queue family indices.
        u32 graphicsFamily;
        u32 presentFamily;
        VulkanUtil::PhysicalDevice.GetQueueFamilyIndices(physicalDevice, surface, &graphicsFamily, &presentFamily);
        u32 queueFamilyIndices[] = {graphicsFamily, presentFamily};

        // Create the swap chain create info.
        VkSwapchainCreateInfoKHR swapChainCreateInfo = {};
        swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapChainCreateInfo.surface = surface;
        swapChainCreateInfo.minImageCount = imageCount;
        swapChainCreateInfo.imageFormat = surfaceFormat.format;
        swapChainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
        swapChainCreateInfo.imageExtent = extent;
        swapChainCreateInfo.imageArrayLayers = 1;
        swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        // If the graphics family and present family are different, then we need to use concurrent sharing mode.
        if (graphicsFamily != presentFamily)
        {
            swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            swapChainCreateInfo.queueFamilyIndexCount = 2;
            swapChainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
            swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            swapChainCreateInfo.queueFamilyIndexCount = 0;
            swapChainCreateInfo.pQueueFamilyIndices = nullptr;
        }

        swapChainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
        swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapChainCreateInfo.presentMode = presentMode;
        swapChainCreateInfo.clipped = VK_TRUE;
        swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

        // Create the swap chain.
        VkSwapchainKHR swapChain;
        if (vkCreateSwapchainKHR(device, &swapChainCreateInfo, nullptr, &swapChain) != VK_SUCCESS)
        {
            std::string msg = "VulkanSwapChainKHRUtil::Create: Failed to create swap chain.";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        LOG("VulkanSwapChainKHRUtil::Create: Successfully created swap chain.");

        // SWAP CHAIN IMAGES
        u32 swapchainImageCount;
        vkGetSwapchainImagesKHR(device, swapChain, &swapchainImageCount, nullptr);
        outImages->resize(imageCount);

        // Get the swap chain images.
        vkGetSwapchainImagesKHR(device, swapChain, &swapchainImageCount, outImages->data());

        // Set the out format.
        *outFormat = surfaceFormat.format;

        // Set the out extent.
        *outExtent = extent;

        return swapChain;
    }

    void VulkanSwapChainKHRUtil::Destroy(const VkDevice &device, VkSwapchainKHR swapchain)
    {
        vkDestroySwapchainKHR(device, swapchain, nullptr);
        LOG("VulkanSwapChainKHRUtil::Destroy: Swapchain destroyed.\n");
    }
}

#endif