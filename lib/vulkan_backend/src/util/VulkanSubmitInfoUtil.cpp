#if USE_VULKAN

#include "util/VulkanSubmitInfoUtil.hpp"
#include <string>
#include <stdexcept>
#include "Types.hpp"

namespace bns 
{
    VkSubmitInfo VulkanSubmitInfoUtil::Create(
        const std::vector<VkSemaphore>& waitSemaphores,
        const std::vector<VkPipelineStageFlags>& waitStages,
        const std::vector<VkCommandBuffer>& commandBuffers,
        const std::vector<VkSemaphore>& signalSemaphores
    )
    {
        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        // Wait on these semaphores before executing the command buffers.
        submitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
        submitInfo.pWaitSemaphores = waitSemaphores.data();
        submitInfo.pWaitDstStageMask = waitStages.data();

        // Execute these command buffers.
        submitInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
        submitInfo.pCommandBuffers = commandBuffers.data();

        // Signal these semaphores after executing the command buffers.
        submitInfo.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size());
        submitInfo.pSignalSemaphores = signalSemaphores.data();

        return submitInfo;
    }

    VkSubmitInfo VulkanSubmitInfoUtil::CreateGraphicsSubmitInfo(
        const VkSemaphore& imageAvailableSemaphore,
        const VkPipelineStageFlags& waitStage,
        const VkCommandBuffer commandBuffer,
        const VkSemaphore& renderFinishedSemaphore
    )
    {
        if(waitStage != VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT)
        {
            std::string message = "VulkanSubmitInfoUtil::CreateGraphicsSubmitInfo: waitStage must be VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT";
            LOG( message);
            BREAKPOINT();
            throw std::runtime_error(message);
        }

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        // Wait on these semaphores before executing the command buffers.
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &imageAvailableSemaphore;
        submitInfo.pWaitDstStageMask = &waitStage;

        // Execute these command buffers.
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        // Signal these semaphores after executing the command buffers.
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &renderFinishedSemaphore;

        return submitInfo;
    }
}

#endif 