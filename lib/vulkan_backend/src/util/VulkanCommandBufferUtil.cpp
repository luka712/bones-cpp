#if USE_VULKAN

#include "util/VulkanCommandBufferUtil.hpp"
#include <string>
#include <stdexcept>
#include "Types.hpp"

namespace bns
{
    VkCommandBuffer VulkanCommandBufferUtil::Create(
        const VkDevice &device,
        const VkCommandPool &commandPool,
        VkCommandBufferLevel level)
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
            LOG( msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }

        return commandBuffer;
    }

    void VulkanCommandBufferUtil::SingleTimeCommand(
        const VkDevice &device,
        const VkCommandPool &commandPool,
        const VkQueue &queue,
        std::function<void(const VkCommandBuffer &)> callback)
    {
        VkCommandBuffer commandBuffer = Create(device, commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);

        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT; // we're only using the command buffer once, so set this flag

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        // CALLBACK
        callback(commandBuffer);

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;           // submit a single command buffer
        submitInfo.pCommandBuffers = &commandBuffer; // the command buffer to submit.

        vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE); // usually graphics queue
        vkQueueWaitIdle(queue);                               // wait for the queue to finish

        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
    }

} // namespace bns

#endif