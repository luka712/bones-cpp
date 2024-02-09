#if USE_VULKAN

#include "util/VulkanPipelineUtil.hpp"
#include "bns_types.hpp"
#include <stdexcept>
#include "VulkanUtil.hpp"

namespace bns
{
    VkPipeline VulkanPipelineUtil::Create(
        VkDevice device,
        const VkShaderModule &vertexShaderModule, const VkShaderModule &fragmentShaderModule,
        const VkPipelineVertexInputStateCreateInfo &vertexInputInfo,
        const VkRenderPass &renderPass,
        const VkPipelineLayout &pipelineLayout,
        const VkExtent2D &swapchainExtent,
        std::string vertexShaderMainName,
        std::string fragmentShaderMainName,
        FrontFace frontFace)
    {
        // SHADER STAGE INFO
        VkPipelineShaderStageCreateInfo shadersStagesInfo[2];
        VulkanUtil::PipelineShaderStageCreateInfo.SetVertexStageInfo(shadersStagesInfo[0], vertexShaderModule);
        VulkanUtil::PipelineShaderStageCreateInfo.SetFragmentStageInfo(shadersStagesInfo[1], fragmentShaderModule);

        // INPUT ASSEMBLY INFO
        VkPipelineInputAssemblyStateCreateInfo inputAssembly = VulkanUtil::PipelineInputAssemblyStateCreateInfo.CreateWithTriangleListTopology();

        // VIEWPORT INFO
        VkViewport viewport = VulkanUtil::Viewport.Create(swapchainExtent);

        // SCISSOR INFO
        VkRect2D scissor = {};
        scissor.offset = {0, 0};
        scissor.extent = swapchainExtent;

        // VIEWPORT STATE INFO
        VkPipelineViewportStateCreateInfo viewportState = VulkanUtil::PipelineViewportStateCreateInfo.Create(viewport, scissor);

        // RASTERIZER INFO
        VkPipelineRasterizationStateCreateInfo rasterizer = VulkanUtil::PipelineRasterizationStateCreateInfo.Create(frontFace, CullMode::Back);

        // MULTISAMPLING INFO - we are not using multisampling
        VkPipelineMultisampleStateCreateInfo multisampling = VulkanUtil::PipelineMultisampleStateCreateInfo.CreateMSAADisabled();

        // COLOR BLENDING INFO
        VkPipelineColorBlendAttachmentState colorBlendAttachment = VulkanUtil::PipelineColorBlendAttachmentState.Create();
        VkPipelineColorBlendStateCreateInfo colorBlending = VulkanUtil::PipelineColorBlendStateCreateInfo.Create(colorBlendAttachment);

        // DYNAMIC STATE INFO
        std::vector<VkDynamicState> dynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_LINE_WIDTH,
            VK_DYNAMIC_STATE_SCISSOR};
        VkPipelineDynamicStateCreateInfo dynamicState = VulkanUtil::PipelineDynamicStateCreateInfo.Create(dynamicStates);

        LOG("VulkanPipelineUtil::Create: Created pipeline layout.\n");

        // CREATE PIPELINE
        VkGraphicsPipelineCreateInfo pipelineInfo = {};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.pNext = nullptr;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = &shadersStagesInfo[0];
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = nullptr; // optional
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = &dynamicState;
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // optional
        pipelineInfo.basePipelineIndex = -1;              // optional

        VkPipeline pipeline;
        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline) != VK_SUCCESS)
        {
            std::string msg = "VulkanPipelineUtil::Create: Failed to create graphics pipeline!";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
        return pipeline;
    }

    VkPipeline VulkanPipelineUtil::Create(
        VkDevice device,
        const VkShaderModule &vertexShaderModule, const VkShaderModule &fragmentShaderModule,
        const VkPipelineVertexInputStateCreateInfo &vertexInputInfo,
        const VkRenderPass &renderPass,
        const VkPipelineLayout &pipelineLayout,
        std::string vertexShaderMainName,
        std::string fragmentShaderMainName,
        FrontFace frontFace)
    {
        // SHADER STAGE INFO
        VkPipelineShaderStageCreateInfo shadersStagesInfo[2];
        VulkanUtil::PipelineShaderStageCreateInfo.SetVertexStageInfo(shadersStagesInfo[0], vertexShaderModule);
        VulkanUtil::PipelineShaderStageCreateInfo.SetFragmentStageInfo(shadersStagesInfo[1], fragmentShaderModule);

        // INPUT ASSEMBLY INFO
        VkPipelineInputAssemblyStateCreateInfo inputAssembly = VulkanUtil::PipelineInputAssemblyStateCreateInfo.CreateWithTriangleListTopology();

        // RASTERIZER INFO
        VkPipelineRasterizationStateCreateInfo rasterizer = VulkanUtil::PipelineRasterizationStateCreateInfo.Create(frontFace, CullMode::Back);

        // MULTISAMPLING INFO - we are not using multisampling
        VkPipelineMultisampleStateCreateInfo multisampling = VulkanUtil::PipelineMultisampleStateCreateInfo.CreateMSAADisabled();

        // COLOR BLENDING INFO
        VkPipelineColorBlendAttachmentState colorBlendAttachment = VulkanUtil::PipelineColorBlendAttachmentState.Create();
        VkPipelineColorBlendStateCreateInfo colorBlending = VulkanUtil::PipelineColorBlendStateCreateInfo.Create(colorBlendAttachment);

        // DYNAMIC STATE INFO
        std::vector<VkDynamicState> dynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR};
        VkPipelineDynamicStateCreateInfo dynamicState = VulkanUtil::PipelineDynamicStateCreateInfo.Create(dynamicStates);

        VkPipelineViewportStateCreateInfo pipelineStateCreateInfo = VulkanUtil::PipelineViewportStateCreateInfo.Default();

        LOG("VulkanPipelineUtil::Create: Created pipeline layout.\n");

        // CREATE PIPELINE
        VkGraphicsPipelineCreateInfo pipelineInfo = {};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.pNext = nullptr;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = &shadersStagesInfo[0];
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &pipelineStateCreateInfo; 
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = nullptr; // optional
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.pDynamicState = &dynamicState;
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // optional
        pipelineInfo.basePipelineIndex = -1;              // optional

        VkPipeline pipeline;
        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline) != VK_SUCCESS)
        {
            std::string msg = "VulkanPipelineUtil::Create: Failed to create graphics pipeline!";
            LOG(msg);
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
        return pipeline;
    }
}

#endif