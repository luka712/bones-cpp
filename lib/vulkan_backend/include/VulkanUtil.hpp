#if USE_VULKAN

#ifndef BNS_VULKAN_UTIL_HPP

#define BNS_VULKAN_UTIL_HPP

#include "util/VulkanAttachmentDescriptionUtil.hpp"
#include "util/vulkanAttachmentReferenceUtil.hpp"
#include "util/VulkanSubpassDescriptionUtil.hpp"
#include "util/VulkanRenderPassUtil.hpp"
#include "util/VulkanFramebufferUtil.hpp"
#include "util/VulkanCommandPoolUtil.hpp"
#include "util/VulkanCommandBufferUtil.hpp"
#include "util/VulkanCommandBufferBeginInfoUtil.hpp"
#include "util/VulkanRenderPassBeginInfoUtil.hpp"
#include "util/VulkanVIewportUtil.hpp"
#include "util/VulkanSemaphoreUtil.hpp"
#include "util/VulkanFenceUtil.hpp"
#include "util/VulkanSubmitInfoUtil.hpp"
#include "util/VulkanQueueCreateInfoUtil.hpp"
#include "util/VulkanDeviceUtil.hpp"
#include "util/VulkanVertexInputBindingDescriptionUtil.hpp"
#include "util/VulkanPipelineVertexInputStateCreateInfoUtil.hpp"
#include "util/VulkanShaderModuleUtil.hpp"
#include "util/VulkanPipelineShaderStageCreateInfoUtil.hpp"
#include "util/VulkanDescriptorSetLayoutBindingUtil.hpp"
#include "util/VulkanPipelineDynamicStateCreateInfoUtil.hpp"
#include "util/VulkanPipelineInputAssemblyStateCreateInfoUtil.hpp"
#include "util/VulkanPipelineViewportStateCreateInfoUtil.hpp"
#include "util/VulkanPipelineRasterizationStateCreateInfoUtil.hpp"
#include "util/VulkanPipelineColorBlendAttachmentStateUtil.hpp"
#include "util/VulkanPipelineMultisampleStateCreateInfoUtil.hpp"
#include "util/VulkanPipelineColorBlendStateCreateInfoUtil.hpp"
#include "util/VulkanPipelineLayoutUtil.hpp"
#include "util/VulkanApplicationInfoUtil.hpp"
#include "util/VulkanInstanceUtil.hpp"
#include "util/VulkanPhysicalDeviceUtil.hpp"
#include "util/VulkanDeviceQueueCreateInfoUtil.hpp"
#include "util/VulkanDebugUtilsMessengerEXTUtil.hpp"
#include "util/VulkanSwapChainKHRUtil.hpp"
#include "util/VulkanImageViewUtil.hpp"
#include "util/VulkanPipelineUtil.hpp"
#include "util/VulkanPushConstantRangeUtil.hpp"
#include "util/VulkanBUfferUtil.hpp"
#include "util/VulkanDescriptorSetLayoutUtil.hpp"
#include "util/VulkanDescriptorPoolUtil.hpp"
#include "util/VulkanDescriptorSetUtil.hpp"

namespace bns
{
    struct VulkanUtil
    {
        /// @brief The @ref VulkanApplicationInfoUtil for working with @ref VkApplicationInfo
        static VulkanApplicationInfoUtil ApplicationInfo;

        /// @brief The @ref VulkanAttachmentDescriptionUtil for working with @ref VkAttachmentDescription
        static VulkanAttachmentDescriptionUtil AttachmentDescription;

        /// @brief The @ref VulkanAttachmentReferenceUtil for working with @ref VkAttachmentReference
        static VulkanAttachmentReferenceUtil AttachmentReference;

        /// @brief The @ref VulkanBufferUtil for working with @ref VkBuffer
        static VulkanBufferUtil Buffer;

        /// @brief The @ref VulkanCommandBufferUtil for working with @ref VkCommandBuffer
        static VulkanCommandBufferUtil CommandBuffer;

        /// @brief The @ref VulkanCommandBufferBeginInfoUtil for working with @ref VkCommandBufferBeginInfo
        static VulkanCommandBufferBeginInfoUtil CommandBufferBeginInfo;

        /// @brief The @ref VulkanCommandPoolUtil for working with @ref VkCommandPool
        static VulkanCommandPoolUtil CommandPool;

        /// @brief The @ref VulkanDebugUtilsMessengerEXTUtil for working with @ref VkDebugUtilsMessengerEXT
        static VulkanDebugUtilsMessengerEXTUtil DebugUtilsMessengerEXT;

        /// @brief The @ref VulkanDescriptorSetUtil for working with @ref VkDescriptorSet
        static VulkanDescriptorSetUtil DescriptorSet;

        /// @brief The @ref VulkanDescriptorSetLayoutBindingUtil for working with @ref VkDescriptorSetLayoutBinding
        static VulkanDescriptorSetLayoutBindingUtil DescriptorSetLayoutBinding;

        /// @brief The @ref VulkanDescriptorSetLayoutUtil for working with @ref VkDescriptorSetLayout
        static VulkanDescriptorSetLayoutUtil DescriptorSetLayout;

        /// @brief The @ref VulkanDescriptorPoolUtil for working with @ref VkDescriptorPool
        static VulkanDescriptorPoolUtil DescriptorPool;

        /// @brief The @ref VulkanDeviceUtil for working with @ref VkDevice
        static VulkanDeviceUtil Device;

        /// @brief The @ref VulkanDeviceQueueCreateInfoUtil for working with @ref VkDeviceQueueCreateInfo
        static VulkanDeviceQueueCreateInfoUtil DeviceQueueCreateInfo;

        /// @brief The @ref VulkanFenceUtil for working with @ref VkFence
        static VulkanFenceUtil Fence;

        /// @brief The @ref VulkanFramebufferUtil for working with @ref VkFramebuffer
        static VulkanFramebufferUtil Framebuffer;

        /// @brief The @ref VulkanImageViewUtil for working with @ref VkImageView
        static VulkanImageViewUtil ImageView;

        /// @brief The @ref VulkanSemaphoreUtil for working with @ref VkSemaphore
        static VulkanSemaphoreUtil Semaphore;

        /// @brief The @ref VulkanShaderModuleUtil for working with @ref VkShaderModule
        static VulkanShaderModuleUtil ShaderModule;

        /// @brief The @ref VulkanSubmitInfoUtil for working with @ref VkSubmitInfo
        static VulkanSubmitInfoUtil SubmitInfo;

        /// @brief The @ref VulkanSwapChainKHRUtil for working with @ref VkSwapchainKHR
        static VulkanSwapChainKHRUtil SwapChainKHR;

        /// @brief The @ref VulkanSubpassDescriptionUtil for working with @ref VkSubpassDescription
        static VulkanSubpassDescriptionUtil SubpassDescription;

        /// @brief The @ref VulkanPhysicalDeviceUtil for working with @ref VkPhysicalDevice
        static VulkanPhysicalDeviceUtil PhysicalDevice;

        /// @brief The @ref VulkanPipelineUtil for working with @ref VkPipeline
        static VulkanPipelineUtil Pipeline;

        /// @brief The @ref VulkanPipelineColorBlendAttachmentStateUtil for working with @ref VkPipelineColorBlendAttachmentState
        static VulkanPipelineColorBlendAttachmentStateUtil PipelineColorBlendAttachmentState;

        /// @brief The @ref VulkanPipelineColorBlendStateCreateInfoUtil for working with @ref VkPipelineColorBlendStateCreateInfo
        static VulkanPipelineColorBlendStateCreateInfoUtil PipelineColorBlendStateCreateInfo;

        /// @brief The @ref VulkanPipelineDynamicStateCreateInfoUtil for working with @ref VkPipelineDynamicStateCreateInfo
        static VulkanPipelineDynamicStateCreateInfoUtil PipelineDynamicStateCreateInfo;

        /// @brief The @ref VulkanPipelineInputAssemblyStateCreateInfoUtil for working with @ref VkPipelineInputAssemblyStateCreateInfo
        static VulkanPipelineInputAssemblyStateCreateInfoUtil PipelineInputAssemblyStateCreateInfo;

        /// @brief The @ref VulkanPipelineMultisampleStateCreateInfoUtil for working with @ref VkPipelineMultisampleStateCreateInfo
        static VulkanPipelineMultisampleStateCreateInfoUtil PipelineMultisampleStateCreateInfo;

        /// @brief The @ref VulkanPipelineLayoutUtil for working with @ref VkPipelineLayout
        static VulkanPipelineLayoutUtil PipelineLayout;

        /// @brief The @ref VulkanPipelineRasterizationStateCreateInfoUtil for working with @ref VkPipelineRasterizationStateCreateInfo
        static VulkanPipelineRasterizationStateCreateInfoUtil PipelineRasterizationStateCreateInfo;

        /// @brief The @ref VulkanPipelineVertexInputStateCreateInfoUtil for working with @ref VkPipelineVertexInputStateCreateInfo
        static VulkanPipelineVertexInputStateCreateInfoUtil PipelineVertexInputStateCreateInfo;

        /// @brief The @ref VulkanPipelineViewportStateCreateInfoUtil for working with @ref VkPipelineViewportStateCreateInfo
        static VulkanPipelineViewportStateCreateInfoUtil PipelineViewportStateCreateInfo;

        /// @brief The @ref VulkanPipelineShaderStageCreateInfoUtil for working with @ref VkPipelineShaderStageCreateInfo
        static VulkanPipelineShaderStageCreateInfoUtil PipelineShaderStageCreateInfo;

        /// @brief The @ref VulkanRenderPassUtil for working with @ref VkRenderPass
        static VulkanRenderPassUtil RenderPass;

        /// @brief The @ref VulkanRenderPassBeginInfoUtil for working with @ref VkRenderPassBeginInfo
        static VulkanRenderPassBeginInfoUtil RenderPassBeginInfo;

        /// @brief The @ref VulkanPushConstantRangeUtil for working with @ref VkPushConstantRange
        static VulkanPushConstantRangeUtil PushConstantRange;

        /// @brief The @ref VulkanQueueCreateInfoUtil for working with @ref VkDeviceQueueCreateInfo
        static VulkanQueueCreateInfoUtil QueueCreateInfo;

        /// @brief The @ref VulkanVertexInputBindingDescriptionUtil for working with @ref VkVertexInputBindingDescription
        static VulkanVertexInputBindingDescriptionUtil VertexInputBindingDescription;

        /// @brief The @ref VulkanViewportUtil for working with @ref VkViewport
        static VulkanViewportUtil Viewport;

        /// @brief The @ref VulkanInstanceUtil for working with @ref VkInstance
        static VulkanInstanceUtil Instance;
    };
}

#endif

#endif