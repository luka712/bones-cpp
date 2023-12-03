#if USE_VULKAN

#include "util/VulkanCommandBufferBeginInfoUtil.hpp"

namespace bns
{
    VkCommandBufferBeginInfo VulkanCommandBufferBeginInfoUtil::Create()
    {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;                  // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional
        return beginInfo;
    }
} // namespace bns

#endif