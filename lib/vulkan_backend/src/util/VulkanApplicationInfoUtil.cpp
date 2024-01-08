#if USE_VULKAN

#include "util/VulkanApplicationInfoUtil.hpp"

namespace bns
{
    VkApplicationInfo VulkanApplicationInfoUtil::Create()
    {
        VkApplicationInfo appInfo{};
        appInfo.pNext = nullptr;
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Bones Framework";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Bones Framework";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

        return appInfo;
    }
}

#endif