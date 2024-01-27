#if USE_VULKAN

#ifndef BNS_VULKAN_PIPELINE_UTIL_HPP

#define BNS_VULKAN_PIPELINE_UTIL_HPP

#include "BnsVulkan.hpp"
#include <string>
#include "RenderingBackendTypes.hpp"

namespace bns
{
    /// @brief Utility class for creating @ref VkPipelineVertexInputStateCreateInfo structs
    struct VulkanPipelineUtil final
    {
        /// @brief Creates a @ref VkPipeline object.
        /// @param device The device.
        /// @param vertexShaderModule The vertex shader module. 
        /// @param fragmentShaderModule The fragment shader module.
        /// @param vertexInputInfo The vertex input info. This is used to specify the vertex input format.
        /// @param renderPass The render pass.
        /// @param pipelineLayout The pipeline layout.
        /// @param swapchainExtent The swapchain extent.
        /// @param vertexShaderMainName The vertex shader main name. By default it is "main".
        /// @param fragmentShaderMainName The fragment shader main name By default it is "main".
        /// @param frontFace The front face of the vertices in the scene. By default it is clockwise. Vulkan is exception to other apis here because we are flipping the y axis of the viewport.
        /// @return The created @ref VkPipeline object.
        static VkPipeline Create(
            VkDevice device,
            const VkShaderModule &vertexShaderModule, const VkShaderModule &fragmentShaderModule,
            const VkPipelineVertexInputStateCreateInfo& vertexInputInfo,
            const VkRenderPass &renderPass,
            const VkPipelineLayout &pipelineLayout,
            const VkExtent2D& swapchainExtent,
            std::string vertexShaderMainName = "vs_main", 
            std::string fragmentShaderMainName = "fs_main",
            FrontFace frontFace = FrontFace::Clockwise);


             /// @brief Creates a @ref VkPipeline object.
        /// @param device The device.
        /// @param vertexShaderModule The vertex shader module. 
        /// @param fragmentShaderModule The fragment shader module.
        /// @param vertexInputInfo The vertex input info. This is used to specify the vertex input format.
        /// @param renderPass The render pass.
        /// @param pipelineLayout The pipeline layout.
        /// @param vertexShaderMainName The vertex shader main name. By default it is "main".
        /// @param fragmentShaderMainName The fragment shader main name By default it is "main".
        /// @param frontFace The front face of the vertices in the scene. By default it is clockwise. Vulkan is exception to other apis here because we are flipping the y axis of the viewport.
        /// @return The created @ref VkPipeline object.
        static VkPipeline Create(
            VkDevice device,
            const VkShaderModule &vertexShaderModule, const VkShaderModule &fragmentShaderModule,
            const VkPipelineVertexInputStateCreateInfo& vertexInputInfo,
            const VkRenderPass &renderPass,
            const VkPipelineLayout &pipelineLayout,
            std::string vertexShaderMainName = "vs_main", 
            std::string fragmentShaderMainName = "fs_main",
            FrontFace frontFace = FrontFace::Clockwise);
    };
}

#endif // !BNS_VULKAN_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO_UTIL_HPP

#endif