#if USE_VULKAN

#include "util/VulkanQueueCreateInfoUtil.hpp"

namespace bns
{
    VkDeviceQueueCreateInfo VulkanQueueCreateInfoUtil::Create(u32 queueFamilyIndex, const std::vector<f32>& queuePriorities)
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = static_cast<u32>(queuePriorities.size());
        queueCreateInfo.pQueuePriorities = queuePriorities.data();

        return queueCreateInfo;
    }
}

#endif 