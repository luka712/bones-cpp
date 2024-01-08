#if USE_VULKAN

#include "util/VulkanFenceUtil.hpp"
#include <string>
#include "Types.hpp"
#include <stdexcept>

namespace bns
{
    VkFence VulkanFenceUtil::Create(VkDevice device, VkFenceCreateFlags createFlags)
    {
        VkFenceCreateInfo fenceCreateInfo = {};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceCreateInfo.flags = createFlags;

        VkFence fence;
        if (vkCreateFence(device, &fenceCreateInfo, nullptr, &fence) != VK_SUCCESS)
        {
            std::string msg = "VulkanFenceUtil::Create: Failed to create fence";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return fence;
    }

    void VulkanFenceUtil::Destroy(VkDevice device, VkFence fence)
    {
        vkDestroyFence(device, fence, nullptr);
    }
}

#endif 