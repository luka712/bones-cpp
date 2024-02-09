#if USE_VULKAN

#include "util/VulkanInstanceUtil.hpp"
#include "CharUtil.hpp"
#include <stdexcept>
#include "bns_types.hpp"

namespace bns
{
    bool VulkanInstanceUtil::IsExtensionSupported(const std::string &extensionName)
    {
        u32 extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        for (const VkExtensionProperties &extension : extensions)
        {
            if (strcmp(extension.extensionName, extensionName.c_str()) == 0)
            {
                return true;
            }
        }

        return false;
    }

    bool VulkanInstanceUtil::IsLayerSupported(const std::string &layerName)
    {
        u32 layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> layers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

        for (const VkLayerProperties &layer : layers)
        {
            if (strcmp(layer.layerName, layerName.c_str()) == 0)
            {
                return true;
            }
        }

        return false;
    }

    void VulkanInstanceUtil::PrintAvailableExtensionsAndLayers()
    {
        u32 extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        LOG("VulkanInstanceUtil::PrintAvailableExtensionsAndLayers: Available extensions:\n");
        for (const VkExtensionProperties &extension : extensions)
        {
            LOG("\t" + std::string(extension.extensionName));
        }

        u32 layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> layers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

        LOG("VulkanInstanceUtil::PrintAvailableExtensionsAndLayers: Available layers:");
        for (const VkLayerProperties &layer : layers)
        {
            LOG("\t" + std::string(layer.layerName));
        }
    }

    VkInstance VulkanInstanceUtil::Create(const std::vector<std::string> &enableExtensions,
                                          const std::vector<std::string> &enableLayers,
                                          std::string applicationName)
    {
        LOG("VulkanInstanceUtil::Create: Creating Vulkan instance...");

        // LOG REQUIRED EXTENSIONS
        LOG("VulkanInstanceUtil::Create: Required extensions:");
        for (const std::string &extension : enableExtensions)
        {
            LOG("\t" + extension);
        }

        // LOG REQUIRED LAYERS
        LOG("VulkanInstanceUtil::Create: Required layers:");
        for (const std::string &layer : enableLayers)
        {
            LOG("\t" + layer);
        }

        VkInstance instance = VK_NULL_HANDLE;

        // APPLICATION INFO
        VkApplicationInfo applicationInfo{};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName = applicationName.c_str();
        applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 1, 0);
        applicationInfo.pEngineName = "Bones Framework";
        applicationInfo.engineVersion = VK_MAKE_VERSION(1, 1, 0);
        applicationInfo.apiVersion = VK_API_VERSION_1_1;

        // INSTANCE CREATE INFO
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &applicationInfo;

        // VALIDATE EXTENSIONS
        for (const std::string &extension : enableExtensions)
        {
            if (!IsExtensionSupported(extension))
            {
                std::string msg = "VulkanInstanceUtil::Create: Extension '" + extension + "' not supported.";
                LOG(msg);
                BREAKPOINT();
                throw std::runtime_error(msg.c_str());
            }
        }

        // SETUP EXTENSIONS
        createInfo.enabledExtensionCount = static_cast<u32>(enableExtensions.size());
        char **pEnabledExtensions = CharUtil::CreateCopy(enableExtensions);
        createInfo.ppEnabledExtensionNames = pEnabledExtensions;

        // VALIDATE LAYERS
        for (const std::string &layer : enableLayers)
        {
            if (!IsLayerSupported(layer))
            {
                std::string msg = "VulkanInstanceUtil::Create: Layer '" + layer + "' not supported.";
                LOG(msg);
                BREAKPOINT();
                throw std::runtime_error(msg.c_str());
            }
        }

        // SETUP LAYERS
        createInfo.enabledLayerCount = static_cast<u32>(enableLayers.size());
        char **pEnabledLayers = CharUtil::CreateCopy(enableLayers);
        createInfo.ppEnabledLayerNames = pEnabledLayers;

        // CREATE INSTANCE
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            std::string msg = "VulkanInstanceUtil::Create: Failed to create Vulkan instance.";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        // RELEASE MEMORY RESOURCES
        CharUtil::FreeCopy(pEnabledExtensions, enableExtensions.size());
        CharUtil::FreeCopy(pEnabledLayers, enableLayers.size());

        LOG("VulkanInstanceUtil::Create: Vulkan instance created.\n");

        return instance;
    }
}

#endif