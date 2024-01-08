#if USE_VULKAN

#include "util/VulkanDeviceQueueCreateInfoUtil.hpp"

namespace bns
{
    VkDeviceQueueCreateInfo VulkanDeviceQueueCreateInfoUtil::Create(u32 queueFamilyIndex, const std::vector<f32>& queuePriorities)
    {
        VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
        deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        deviceQueueCreateInfo.queueCount = static_cast<u32>(queuePriorities.size());
        deviceQueueCreateInfo.pQueuePriorities = queuePriorities.data();

        return deviceQueueCreateInfo;
    }
}

#endif 