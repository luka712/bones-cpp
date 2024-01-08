#if USE_VULKAN

#include "util/VulkanPipelineUtil.hpp"
#include "Types.hpp"
#include <stdexcept>
#include "VulkanUtil.hpp"

namespace bns
{
    VkPipeline VulkanPipelineUtil::Create(
        VkDevice device,
        const VkShaderModule &vertexShaderModule, const VkShaderModule &fragmentShaderModule,
        const VkRenderPass &renderPass,
        const VkExtent2D &swapchainExtent,
        std::string vertexShaderMainName,
        std::string fragmentShaderMainName,
        FrontFace frontFace)
    {
        // VERTEX INPUT INFO - TODO: needs to be passed in
        VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.pNext = nullptr;
        vertexInputInfo.vertexBindingDescriptionCount = 0;
        vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
        vertexInputInfo.vertexAttributeDescriptionCount = 0;
        vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

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
            VK_DYNAMIC_STATE_LINE_WIDTH
        };
        VkPipelineDynamicStateCreateInfo dynamicState = VulkanUtil::PipelineDynamicStateCreateInfo.Create(dynamicStates);

        // PIPELINE LAYOUT 
        std::vector<VkDescriptorSetLayout> descriptorSetLayouts = {};
        VkPipelineLayout pipelineLayout = VulkanUtil::PipelineLayout.Create(device, descriptorSetLayouts);

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
            LOG("%s\n", msg.c_str());
            BREAKPOINT();
            throw std::runtime_error(msg);
        }
        return pipeline;
    }
}

#endif