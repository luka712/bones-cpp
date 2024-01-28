#if USE_VULKAN

#include "util/VulkanImageLayoutUtil.hpp"
#include "VulkanUtil.hpp"
#include <stdexcept>
#include <string>

namespace bns
{
    void VulkanImageLayoutUtil::TransitionImageLayout(
        const VkDevice &device,
        const VkCommandPool &commandPool,
        const VkQueue &queue,
        const VkImage &image,
        VkFormat format,
        VkImageLayout oldLayout,
        VkImageLayout newLayout)
    {
        VulkanUtil::CommandBuffer.SingleTimeCommand(device, commandPool, queue, [&](const VkCommandBuffer &buffer)
                                                    {
                    // https://vulkan-tutorial.com/Texture_mapping/Images 

                    VkImageMemoryBarrier barrier = {};
                    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
                    barrier.oldLayout = oldLayout;
                    barrier.newLayout = newLayout;
                    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
                    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
                    barrier.image = image;
                    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                    barrier.subresourceRange.baseMipLevel = 0;
                    barrier.subresourceRange.levelCount = 1;
                    barrier.subresourceRange.baseArrayLayer = 0;
                    barrier.subresourceRange.layerCount = 1;

                    VkPipelineStageFlags sourceStage;
                    VkPipelineStageFlags destinationStage;

                    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
                    {
                        barrier.srcAccessMask = 0;
                        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

                        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
                        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
                    }
                    else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
                    {
                        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

                        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
                        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
                    }
                    else
                    {
                        std::string msg = "VulkanImageLayoutUtil::TransitionImageLayout: unsupported layout transition!";
                       LOG(msg);
                        BREAKPOINT();
                        throw std::runtime_error(msg);
                    }

                    vkCmdPipelineBarrier(
                        buffer,
                        sourceStage, destinationStage,
                        0,
                        0, nullptr,
                        0, nullptr,
                        1, &barrier); });
    }
}

#endif