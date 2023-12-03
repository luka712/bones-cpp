#if USE_VULKAN

#include "util/VulkanCommandBufferUtil.hpp"
#include <string>
#include <stdexcept>
#include "Types.hpp"

namespace bns
{
    VkCommandBuffer VulkanCommandBufferUtil::Create(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel level)
    {
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = level; // this is the level of the command buffer (primary or secondary) 
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS)
        {
            std::string msg = "VulkanCommandBufferUtil::Create: failed to allocate command buffers!";
            LOG("%s", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return commandBuffer;
    }
} // namespace bns

#endif 