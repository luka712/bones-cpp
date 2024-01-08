#if USE_VULKAN

#include "util/VulkanInstanceUtil.hpp"
#include "CharUtil.hpp"
#include <stdexcept>
#include "Types.hpp"

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
            LOG("\t%s\n", extension.extensionName);
        }

        u32 layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> layers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

        LOG("VulkanInstanceUtil::PrintAvailableExtensionsAndLayers: Available layers:\n");
        for (const VkLayerProperties &layer : layers)
        {
            LOG("\t%s\n", layer.layerName);
        }
    }

    VkInstance VulkanInstanceUtil::Create(const VkApplicationInfo &appInfo,
                                          const std::vector<std::string> &enableExtensions,
                                          const std::vector<std::string> &enableLayers)
    {
        VkInstance instance = VK_NULL_HANDLE;

        // create instance info
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // validate extensions
        for (const std::string &extension : enableExtensions)
        {
            if (!IsExtensionSupported(extension))
            {
                std::string msg = "VulkanInstanceUtil::Create: Extension not supported.";
                LOG(msg.c_str());
                BREAKPOINT();
                throw std::runtime_error(msg.c_str());
            }

            LOG("VulkanInstanceUtil::Create: Extension supported: %s\n", extension.c_str());
        }

        // setup extensions
        createInfo.enabledExtensionCount = static_cast<u32>(enableExtensions.size());
        char **pEnabledExtensions = CharUtil::CreateCopy(enableExtensions);
        createInfo.ppEnabledExtensionNames = pEnabledExtensions;

        // validate layers
        for (const std::string &layer : enableLayers)
        {
            if (!IsLayerSupported(layer))
            {
                std::string msg = "VulkanInstanceUtil::Create: Layer not supported.";
                LOG(msg.c_str());
                BREAKPOINT();
                throw std::runtime_error(msg.c_str());
            }

            LOG("VulkanInstanceUtil::Create: Layer supported: %s\n", layer.c_str());
        }

        // setup layers
        createInfo.enabledLayerCount = static_cast<u32>(enableLayers.size());
        char **pEnabledLayers = CharUtil::CreateCopy(enableLayers);
        createInfo.ppEnabledLayerNames = pEnabledLayers;

        // CREATE INSTANCE
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            std::string msg = "SDLWindowManager::SetupInstance: Failed to create Vulkan instance.";
            LOG(msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg.c_str());
        }

        // release memory
        for (size_t i = 0; i < enableExtensions.size(); i++)
        {
            delete pEnabledExtensions[i];
        }
        delete[] pEnabledExtensions;

        for (size_t i = 0; i < enableLayers.size(); i++)
        {
            delete pEnabledLayers[i];
        }
        delete[] pEnabledLayers;

        return instance;
    }
}

#endif