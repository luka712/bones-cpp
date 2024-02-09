#if USE_VULKAN

#ifndef BNS_VULKAN_SWAP_CHAIN_KHR_UTIL_HPP

#define BNS_VULKAN_SWAP_CHAIN_KHR_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>
#include "bns_types.hpp"

namespace bns
{
    /// @brief The Vulkan swap chain KHR util. Provides utility functions for the Vulkan swap chain KHR.
    class VulkanSwapChainKHRUtil final
    {
    private:
        /// @brief Logs the information about transform bits.
        /// @param transformBits The surface transform bits.
        static void LogTransformBits(VkSurfaceTransformFlagsKHR transformBits);

        /// @brief Logs the information about alpha composite bits.
        /// @param alphaCompositeBits The alpha composite bits.
        static void LogAlphaCompositeBits(VkCompositeAlphaFlagsKHR alphaCompositeBits);

        /// @brief Logs the information about supported image uses.
        /// @param supportedImageUses The supported image uses.
        static void LogSupportedImageUses(VkImageUsageFlags supportedImageUses);

        /// @brief Logs the information about surface capabilities.
        /// @param surfaceCapabilities The surface capabilities.
        static void LogSurfaceCapabilities(VkSurfaceCapabilitiesKHR surfaceCapabilities);

    public:
        /// @brief Chooses the surface format.
        /// @param availableFormats The available formats.
        /// @return The chosen surface format.
        static VkSurfaceFormatKHR ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

        /// @brief Chooses the present mode.
        /// @param availablePresentModes The available present modes.
        /// @return The chosen present mode.
        static VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

        /// @brief Chooses the extent.
        /// @param surfaceCapabilities The surface capabilities.
        /// @param width The width.
        /// @param height The height.
        /// @return The chosen extent.
        static VkExtent2D ChooseExtent(
            const VkSurfaceCapabilitiesKHR &surfaceCapabilities,
            uint32_t width,
            uint32_t height);

        /// @brief Queries the swap chain support.
        /// @param device The Vulkan physical device.
        /// @param surface The Vulkan surface.
        /// @param outSurfaceCapabilities The out surface capabilities. This will be filled.
        /// @param outFormats The out formats. These will be filled.
        /// @param outPresentModes The out present modes. These will be filled.
        static void QuerySwapChainSupport(
            VkPhysicalDevice device,
            VkSurfaceKHR surface,
            VkSurfaceCapabilitiesKHR *outSurfaceCapabilities,
            std::vector<VkSurfaceFormatKHR> *outFormats,
            std::vector<VkPresentModeKHR> *outPresentModes);

        /// @brief Creates a Vulkan swap chain KHR.
        /// @param physicalDevice The Vulkan physical device.
        /// @param device The Vulkan device.
        /// @param surface The Vulkan surface.
        /// @param width The width.
        /// @param height The height.
        /// @param outImages The out images.
        /// @param outFormat The out format.
        /// @param outExtent The out extent.
        /// @return The Vulkan swap chain KHR.
        static VkSwapchainKHR Create(VkPhysicalDevice physicalDevice,
                                     VkDevice device,
                                     VkSurfaceKHR surface,
                                     u32 width, u32 height,
                                     std::vector<VkImage> *outImages,
                                     VkFormat *outFormat,
                                     VkExtent2D *outExtent);

        /// @brief Destroy the swapchain.
        /// @param device The device.
        /// @param swapchain The swapchain.
        static void Destroy(const VkDevice &device, VkSwapchainKHR swapchain);
    };
}

#endif

#endif