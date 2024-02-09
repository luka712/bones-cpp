#if USE_VULKAN

#include "util/VulkanDebugUtilsMessengerEXTUtil.hpp"
#include <string>
#include "bns_types.hpp"
#include <stdexcept>

namespace bns
{
    VkDebugUtilsMessengerEXT VulkanDebugUtilsMessengerEXTUtil::Create(VkInstance instance, PFN_vkDebugUtilsMessengerCallbackEXT callback, void *pUserData)
    {
        VkDebugUtilsMessengerEXT debugMessanger = VK_NULL_HANDLE;

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = callback;
        createInfo.pUserData = pUserData; // Optional

        // load function
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

        // function not found
        if (func == nullptr)
        {
            std::string msg = "VulkanRenderer::SetupDebugUtilsMessengerEXT: Failed to setup debug messenger! Function not found!";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        // if we have function, call it and check result.
        if (func(instance, &createInfo, nullptr, &debugMessanger) != VK_SUCCESS)
        {
            std::string msg = "VulkanRenderer::SetupDebugUtilsMessengerEXT: Failed to setup debug messenger! Function returned error!";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        LOG("VulkanRenderer::SetupDebugUtilsMessengerEXT: Debug messenger setup successfully!\n");

        return debugMessanger;
    }
}

#endif