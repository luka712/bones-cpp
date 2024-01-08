#if USE_VULKAN

#include "util/VulkanPhysicalDeviceUtil.hpp"
#include "Types.hpp"
#include <stdexcept>

namespace bns
{
    std::vector<std::string> VulkanPhysicalDeviceUtil::GetDeviceExtensions(VkPhysicalDevice device)
    {
        u32 extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensions.data());

        std::vector<std::string> extensionNames;

        LOG("Available device extensions:");

        for (const VkExtensionProperties &extension : extensions)
        {

            LOG("\t %s\n", extension.extensionName);
            extensionNames.push_back(extension.extensionName);
        }

        return extensionNames;
    }

    VkPhysicalDeviceProperties VulkanPhysicalDeviceUtil::GetDeviceProperties(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);

        LOG("Device properties:");
        LOG("\t Device name: %s\n", properties.deviceName);
        LOG("\t Device type: %d\n", properties.deviceType);
        LOG("\t API version: %d\n", properties.apiVersion);
        LOG("\t Driver version: %d\n", properties.driverVersion);
        LOG("\t Vendor ID: %d\n", properties.vendorID);
        LOG("\t Device ID: %d\n", properties.deviceID);
        LOG("\t Pipeline cache UUID: %d\n", properties.pipelineCacheUUID);
        LOG("\t Limits:\n");
        LOG("\t\t maxImageDimension1D: %d\n", properties.limits.maxImageDimension1D);
        LOG("\t\t maxImageDimension2D: %d\n", properties.limits.maxImageDimension2D);
        LOG("\t\t maxImageDimension3D: %d\n", properties.limits.maxImageDimension3D);
        LOG("\t\t maxImageDimensionCube: %d\n", properties.limits.maxImageDimensionCube);
        LOG("\t\t maxImageArrayLayers: %d\n", properties.limits.maxImageArrayLayers);
        LOG("\t\t maxTexelBufferElements: %d\n", properties.limits.maxTexelBufferElements);
        LOG("\t\t maxUniformBufferRange: %d\n", properties.limits.maxUniformBufferRange);
        LOG("\t\t maxStorageBufferRange: %d\n", properties.limits.maxStorageBufferRange);
        LOG("\t\t maxPushConstantsSize: %d\n", properties.limits.maxPushConstantsSize);
        LOG("\t\t maxMemoryAllocationCount: %d\n", properties.limits.maxMemoryAllocationCount);
        LOG("\t\t maxSamplerAllocationCount: %d\n", properties.limits.maxSamplerAllocationCount);
        LOG("\t\t bufferImageGranularity: %d\n", properties.limits.bufferImageGranularity);
        LOG("\t\t sparseAddressSpaceSize: %d\n", properties.limits.sparseAddressSpaceSize);
        LOG("\t\t maxBoundDescriptorSets: %d\n", properties.limits.maxBoundDescriptorSets);
        LOG("\t\t maxPerStageDescriptorSamplers: %d\n", properties.limits.maxPerStageDescriptorSamplers);
        LOG("\t\t maxPerStageDescriptorUniformBuffers: %d\n", properties.limits.maxPerStageDescriptorUniformBuffers);

        return properties;
    }

    bool VulkanPhysicalDeviceUtil::IsDeviceSuitable(VkPhysicalDevice device, const std::vector<std::string> &requiredExtensions)
    {
        std::vector<std::string> availableExtensions = GetDeviceExtensions(device);

        LOG("Checking device suitability...");

        for (const std::string &requiredExtension : requiredExtensions)
        {
            LOG("Required extension: %s", requiredExtension.c_str());

            bool extensionFound = false;
            for (const std::string &availableExtension : availableExtensions)
            {
                if (requiredExtension == availableExtension)
                {
                    extensionFound = true;
                    LOG("Extension found: %s", availableExtension.c_str());
                    break;
                }
            }

            if (!extensionFound)
            {
                std::string msg = "VulkanPhysicalDeviceUtil::IsDeviceSuitable: Device does not support required extension: " + requiredExtension;
                LOG(msg.c_str());
                BREAKPOINT();
                throw std::runtime_error(msg);
            }
        }

        return true;
    }

    VkPhysicalDevice VulkanPhysicalDeviceUtil::PickPhysicalDevice(VkInstance instance, const std::vector<std::string> &requiredExtensions)
    {
        // Get the number of physical devices.
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            std::string msg = "VulkanPhysicalDeviceUtil::PickPhysicalDevice: No physical devices found.";
            LOG(msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        // Get all physical devices.
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        // Find the first suitable device (discrete GPU preferred).
        for (const VkPhysicalDevice &device : devices)
        {
            LOG("Checking for discrete GPU device...");
            VkPhysicalDeviceProperties properties = GetDeviceProperties(device);

            // Prefer discrete GPUs.
            if (IsDeviceSuitable(device, requiredExtensions) && properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
                return device;
            }
        }

        // Find the first suitable device (integrated GPU preferred).
        for (const VkPhysicalDevice &device : devices)
        {
            LOG("Checking for integrated GPU device...");
            VkPhysicalDeviceProperties properties = GetDeviceProperties(device);

            // Prefer discrete GPUs.
            if (IsDeviceSuitable(device, requiredExtensions) && properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
                return device;
        }

        // No suitable device found.
        std::string msg = "VulkanPhysicalDeviceUtil::PickPhysicalDevice: No suitable physical device found.";
        LOG(msg.c_str());
        BREAKPOINT();
        throw std::runtime_error(msg);
    }

    void VulkanPhysicalDeviceUtil::GetQueueFamilyIndices(VkPhysicalDevice device, VkSurfaceKHR surface, u32 *graphicsFamily, u32 *presentFamily)
    {
        // Set to invalid value.
        *graphicsFamily = UINT32_MAX;
        *presentFamily = UINT32_MAX;

        // Get the number of queue families.
        u32 queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        // Get all queue families.
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        // Find the first queue family that supports graphics.
        for (u32 i = 0; i < queueFamilies.size(); i++)
        {
            const VkQueueFamilyProperties &queueFamily = queueFamilies[i];

            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                *graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport)
            {
                *presentFamily = i;
            }

            // If both queue families are valid, we can stop searching.
            if (*graphicsFamily != UINT32_MAX && *presentFamily != UINT32_MAX)
            {
                break;
            }
        }

        // Validate
        if (*graphicsFamily == UINT32_MAX)
        {
            std::string msg = "VulkanPhysicalDeviceUtil::GetQueueFamilyIndices: No graphics queue family found.";
            LOG(msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        if (*presentFamily == UINT32_MAX)
        {
            std::string msg = "VulkanPhysicalDeviceUtil::GetQueueFamilyIndices: No present queue family found.";
            LOG(msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
    }
}

#endif