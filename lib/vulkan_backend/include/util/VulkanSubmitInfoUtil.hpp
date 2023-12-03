#if USE_VULKAN

#ifndef VULKAN_SUBMIT_INFO_UTIL_HPP

#define VULKAN_SUBMIT_INFO_UTIL_HPP

#include "BnsVulkan.hpp"
#include <vector>

namespace bns 
{
    struct VulkanSubmitInfoUtil
    {
        /// @brief Create a @ref VkSubmitInfo struct with the given parameters.
        /// @param waitSemaphores The semaphores to wait on before executing the command buffers.
        /// @param waitStages The stages to wait on before executing the command buffers.
        /// @param commandBuffers The command buffers to execute.
        /// @param signalSemaphores The semaphores to signal after executing the command buffers.
        /// @return The created @ref VkSubmitInfo struct.
        static VkSubmitInfo Create(
            const std::vector<VkSemaphore>& waitSemaphores,
            const std::vector<VkPipelineStageFlags>& waitStages,
            const std::vector<VkCommandBuffer>& commandBuffers,
            const std::vector<VkSemaphore>& signalSemaphores
        );

        /// @brief Create a @ref VkSubmitInfo struct with the given parameters.
        /// @param imageAvailableSemaphore The semaphore to wait on before executing the command buffer.
        /// @param waitStage The stage to wait on before executing the command buffer. Must be @ref VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
        /// @param commandBuffer The command buffer to execute.
        /// @param renderFinishedSemaphore The semaphore to signal after executing the command buffer.
        /// @return The created @ref VkSubmitInfo struct.
        static VkSubmitInfo CreateGraphicsSubmitInfo(
            const VkSemaphore& imageAvailableSemaphore,
            const VkPipelineStageFlags& waitStage,
            const VkCommandBuffer commandBuffer,
            const VkSemaphore& renderFinishedSemaphore
        );
    };
}

#endif 

#endif 