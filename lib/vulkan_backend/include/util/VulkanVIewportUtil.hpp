#if USE_VULKAN

#ifndef BNS_VULKAN_VIEWPORT_UTIL_HPP

#define BNS_VULKAN_VIEWPORT_UTIL_HPP

#include "Types.hpp"
#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief The util class for working with @ref VkViewport
    struct VulkanViewportUtil final
    {
        /// @brief Get the default @ref VkViewport.
        /// @param width The width of the viewport.
        /// @param height The height of the viewport.
        /// @return The default @ref VkViewport.
        static VkViewport Default(f32 width, f32 height);
 
        /// @brief Get the @ref VkViewport with the y axis flipped. 
        // Reason for this is that Vulkan has the y axis pointing down. 
        // This is not the case for other APIs.
        /// @param width The width of the viewport.
        /// @param height The height of the viewport.
        /// @return The @ref VkViewport with the y axis flipped.
        static VkViewport FlipY(f32 width, f32 height);

        /// @brief Create a @ref VkViewport from the given swapChainExtent vector.
        /// @param swapChainExtent The swap chain extent.
        /// @return The created @ref VkViewport.
        static VkViewport Create(VkExtent2D swapChainExtent);
    };
} // namespace bns

#endif 

#endif