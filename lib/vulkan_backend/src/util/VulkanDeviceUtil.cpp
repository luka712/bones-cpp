#if USE_VULKAN

#include "util/VulkanDeviceUtil.hpp"
#include <string>
#include <stdexcept>
#include "Types.hpp"
#include "CharUtil.hpp"

namespace bns
{
    VkDevice VulkanDeviceUtil::Create(VkPhysicalDevice physicalDevice,
                                      const std::vector<VkDeviceQueueCreateInfo> &queueCreateInfos,
                                      const std::vector<std::string> &deviceExtensions,
                                      const std::vector<std::string> &validationLayers)
    {

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
        deviceFeatures.samplerAnisotropy = VK_TRUE; // enable anisotropy

        VkDevice device = VK_NULL_HANDLE;

        // create device info
        VkDeviceCreateInfo createInfo{};
        createInfo.pNext = nullptr;
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        // queue info
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<u32>(queueCreateInfos.size());

        // device features
        createInfo.pEnabledFeatures = &deviceFeatures;

        // device extensions
        char **pDeviceExtensions = CharUtil::CreateCopy(deviceExtensions);
        createInfo.enabledExtensionCount = static_cast<u32>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = pDeviceExtensions;

        // validation layers
        char **pValidationLayers = CharUtil::CreateCopy(validationLayers);
        createInfo.enabledLayerCount = static_cast<u32>(validationLayers.size());
        createInfo.ppEnabledLayerNames = pValidationLayers;

        // create device
        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
        {
            std::string msg = "VulkanRenderer::SetupLogicalDevice: Failed to create logical device!";
            LOG(msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        for (size_t i = 0; i < deviceExtensions.size(); ++i)
        {
            delete[] pDeviceExtensions[i];
        }

        for (size_t i = 0; i < validationLayers.size(); ++i)
        {
            delete[] pValidationLayers[i];
        }

        delete[] pDeviceExtensions;
        delete[] pValidationLayers;

        return device;
    }
}

#endif