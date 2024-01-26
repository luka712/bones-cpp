#if USE_VULKAN

#ifndef BNS_VULKAN_SAMPLER_UTIL_HPP

#define BNS_VULKAN_SAMPLER_UTIL_HPP

#include "BnsVulkan.hpp"

namespace bns
{
    /// @brief A utility class for working with @ref VkSampler
    struct VulkanSamplerUtil
    {
        /// @brief Creates a @ref VkSampler
        /// @param physicalDevice The physical device to create the sampler on
        /// @param device The device to create the sampler on
        /// @param magFilter The magnification filter. By default this is @ref VK_FILTER_LINEAR
        /// @param minFilter The minification filter. By default this is @ref VK_FILTER_LINEAR
        /// @param addressModeU The address mode for the U coordinate. By default this is @ref VK_SAMPLER_ADDRESS_MODE_REPEAT
        /// @param addressModeV The address mode for the V coordinate. By default this is @ref VK_SAMPLER_ADDRESS_MODE_REPEAT
        /// @param addressModeW The address mode for the W coordinate. By default this is @ref VK_SAMPLER_ADDRESS_MODE_REPEAT
        /// @param outSampler The created sampler
        static VkSampler Create(
            const VkPhysicalDevice &physicalDevice,
            const VkDevice &device,
            VkFilter magFilter = VK_FILTER_LINEAR,
            VkFilter minFilter = VK_FILTER_LINEAR,
            VkSamplerAddressMode addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            VkSamplerAddressMode addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
            VkSamplerAddressMode addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT);

        /// @brief Destroys a @ref VkSampler
        /// @param device The device to destroy the sampler on
        static void Destroy(const VkDevice &device, const VkSampler &sampler);
    };
}

#endif

#endif