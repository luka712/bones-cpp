#if USE_VULKAN

#include "sprite/VulkanUnlitSpritePipeline.hpp"
#include "VulkanUtil.hpp"
#include "FileLoader.hpp"
#include "Mat4x4.hpp"

namespace bns
{
    VulkanUnlitSpritePipeline *VulkanUnlitSpritePipeline::Create(
        const VkDevice &device,
        const VkRenderPass &renderPass,
        u32 framesInFlight,
        const VulkanTexture2D &texture,
        const VkBuffer& projectionViewBuffer)
    {
        // SHADER STAGES
        FileLoader fileLoader;
        std::vector<char> vertexShaderCode = fileLoader.LoadFileAsBinary("shaders/vulkan/sprite/unlit_sprite_vs.spv");
        std::vector<char> fragmentShaderCode = fileLoader.LoadFileAsBinary("shaders/vulkan/sprite/unlit_sprite_fs.spv");
        VkShaderModule vertexShaderModule = VulkanUtil::ShaderModule.CreateFromSpirVSource(device, vertexShaderCode);
        VkShaderModule fragmentShaderModule = VulkanUtil::ShaderModule.CreateFromSpirVSource(device, fragmentShaderCode);

        // Fill shader stage create info
        VkPipelineShaderStageCreateInfo shaderStages[2];
        VulkanUtil::PipelineShaderStageCreateInfo.SetVertexStageInfo(shaderStages[0], vertexShaderModule);
        VulkanUtil::PipelineShaderStageCreateInfo.SetFragmentStageInfo(shaderStages[1], fragmentShaderModule);

        // DYNAMIC STATE - VIEWPORT AND SCISSOR - is not configured here, but in the draw call
        std::vector<VkDynamicState> dynamicStates = VulkanPipelineDynamicStateCreateInfoUtil::DefaultDynamicStates();
        VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = VulkanPipelineDynamicStateCreateInfoUtil::Create(dynamicStates);

        // VIEWPORT
        VkPipelineViewportStateCreateInfo viewportState = VulkanUtil::PipelineViewportStateCreateInfo.Default();

        // INPUT ASSEMBLY - TRIANGLE LIST
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = VulkanPipelineInputAssemblyStateCreateInfoUtil::Default();

        // SETUP VERTEX INPUT
        BufferLayoutDescriptor bufferLayoutDescriptor;
        bufferLayoutDescriptor.Step = VertexStepMode::Vertex;
        bufferLayoutDescriptor.Stride = sizeof(f32) * FLOATS_PER_VERTEX;
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x4, 2, sizeof(f32) * 5});

        std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
        vertexBufferLayouts.push_back(bufferLayoutDescriptor);

        std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
        std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;
        VulkanVertexInputBindingDescriptionUtil::Create(vertexBufferLayouts, vertexInputBindingDescriptions, vertexInputAttributeDescriptions);

        VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo =
            VulkanUtil::PipelineVertexInputStateCreateInfo.Create(vertexInputBindingDescriptions, vertexInputAttributeDescriptions);

        // PIPELINE LAYOUT
        std::vector<VkDescriptorSetLayoutBinding> descriptorSetLayoutBindings = {
            VulkanUtil::DescriptorSetLayoutBinding.CreateUniformForVertexStage(0),
            VulkanUtil::DescriptorSetLayoutBinding.CreateTextureForFragmentStage(1)};

        std::vector<VkDescriptorSetLayout> descriptorSetLayouts = {
            VulkanUtil::DescriptorSetLayout.Create(device, descriptorSetLayoutBindings)};

        VkPipelineLayout pipelineLayout = VulkanUtil::PipelineLayout.Create(device, descriptorSetLayouts);

        // CREATE PIPELINE
        VkPipeline pipeline = VulkanUtil::Pipeline.Create(device,
                                                          vertexShaderModule,
                                                          fragmentShaderModule,
                                                          vertexInputStateCreateInfo,
                                                          renderPass,
                                                          pipelineLayout);

        // CREATE DESCRIPTOR SET
        std::vector<VkDescriptorType> descriptorTypes = {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER};
        VkDescriptorPool descriptorPool = VulkanUtil::DescriptorPool.Create(device, descriptorTypes, framesInFlight);
        std::vector<VkDescriptorSet> descriptorSets = VulkanUtil::DescriptorSet.Create(device, descriptorPool, descriptorSetLayouts, framesInFlight);

        // UPDATE DESCRIPTOR SET
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = projectionViewBuffer;
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(Mat4x4f);

        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = texture.GetImageView();
        imageInfo.sampler = texture.GetSampler();

        std::vector<VulkanUpdateDescriptorDto> updateDescriptorDtos = {
            VulkanUpdateDescriptorDto(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, &bufferInfo),
            VulkanUpdateDescriptorDto(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, nullptr, &imageInfo),
        };

        VulkanUtil::DescriptorSet.Update(device, descriptorSets[0], updateDescriptorDtos);

        // CLEANUP
        vkDestroyShaderModule(device, vertexShaderModule, nullptr);
        vkDestroyShaderModule(device, fragmentShaderModule, nullptr);

        return new VulkanUnlitSpritePipeline(pipeline, pipelineLayout, descriptorPool, descriptorSets);
    }
}

#endif