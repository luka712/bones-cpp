#if USE_VULKAN

#include "util/VulkanSamplerUtil.hpp"
#include <stdexcept>
#include <string>
#include "bns_types.hpp"

namespace bns
{
    VkSampler VulkanSamplerUtil::Create(const VkPhysicalDevice &physicalDevice,
                                        const VkDevice &device,
                                        VkFilter magFilter,
                                        VkFilter minFilter,
                                        VkSamplerAddressMode addressModeU,
                                        VkSamplerAddressMode addressModeV,
                                        VkSamplerAddressMode addressModeW)
    {
        VkSamplerCreateInfo samplerCreateInfo = {};
        samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerCreateInfo.magFilter = magFilter;
        samplerCreateInfo.minFilter = minFilter;
        samplerCreateInfo.addressModeU = addressModeU;
        samplerCreateInfo.addressModeV = addressModeV;
        samplerCreateInfo.addressModeW = addressModeW;
        samplerCreateInfo.anisotropyEnable = VK_TRUE;

        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);

        samplerCreateInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
        samplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;
        samplerCreateInfo.compareEnable = VK_FALSE;
        samplerCreateInfo.compareOp = VK_COMPARE_OP_ALWAYS;
        samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerCreateInfo.mipLodBias = 0.0f;
        samplerCreateInfo.minLod = 0.0f;
        samplerCreateInfo.maxLod = 0.0f;

        VkSampler sampler;
        if (vkCreateSampler(device, &samplerCreateInfo, nullptr, &sampler) != VK_SUCCESS)
        {
            std::string msg = "VulkanSamplerUtil::Create: Failed to create sampler.";
           LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return sampler;
    }
}

#endif