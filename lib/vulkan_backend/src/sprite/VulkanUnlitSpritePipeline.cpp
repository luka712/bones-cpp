// #if USE_VULKAN

// #include "sprite/VulkanUnlitSpritePipeline.hpp"
// #include "VulkanUtil.hpp"
// #include "FileLoader.hpp"

// namespace bns
// {
//     VulkanUnlitSpritePipeline VulkanUnlitSpritePipeline::Create(VkDevice &device,
//                                                                 VulkanTexture2D *texture)
//     {
//         // SHADER STAGES
//         FileLoader fileLoader;
//         std::vector<char> vertexShaderCode = fileLoader.LoadFileAsBinary("shaders/unlit_sprite_vs.spv");
//         std::vector<char> fragmentShaderCode = fileLoader.LoadFileAsBinary("shaders/unlit_sprite_fs.spv");
//         VkShaderModule vertexShaderModule = VulkanUtil::ShaderModule.CreateFromSpirV(device, vertexShaderCode);
//         VkShaderModule fragmentShaderModule = VulkanUtil::ShaderModule.CreateFromSpirV(device, fragmentShaderCode);

//         // Fill shader stage create info
//         VkPipelineShaderStageCreateInfo shaderStages[2];
//         VulkanUtil::PipelineShaderStageCreateInfo.SetVertexStageInfo(shaderStages[0], vertexShaderModule);
//         VulkanUtil::PipelineShaderStageCreateInfo.SetFragmentStageInfo(shaderStages[1], fragmentShaderModule);

//         // DYNAMIC STATE - VIEWPORT AND SCISSOR - is not configured here, but in the draw call
//         std::vector<VkDynamicState> dynamicStates = VulkanPipelineDynamicStateCreateInfoUtil::DefaultDynamicStates();
//         VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = VulkanPipelineDynamicStateCreateInfoUtil::Create(dynamicStates);

//         // VIEWPORT
//         VkPipelineViewportStateCreateInfo viewportState = VulkanUtil::PipelineViewportStateCreateInfo.Default();        

//         // INPUT ASSEMBLY - TRIANGLE LIST
//         VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = VulkanPipelineInputAssemblyStateCreateInfoUtil::Default();

//         // SETUP VERTEX INPUT
//         BufferLayoutDescriptor bufferLayoutDescriptor;
//         bufferLayoutDescriptor.Step = VertexStepMode::Vertex;
//         bufferLayoutDescriptor.Stride = sizeof(f32) * FLOATS_PER_VERTEX;
//         bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
//         bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});
//         bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x4, 2, sizeof(f32) * 5});

//         std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
//         vertexBufferLayouts.push_back(bufferLayoutDescriptor);

//         std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
//         std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;
//         VulkanVertexInputBindingDescriptionUtil::Create(vertexBufferLayouts, vertexInputBindingDescriptions, vertexInputAttributeDescriptions);

//         VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo =
//             VulkanUtil::PipelineVertexInputStateCreateInfo.Create(vertexInputBindingDescriptions, vertexInputAttributeDescriptions);


//         // RASTERIZATION
//         VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = VulkanUtil::PipelineRasterizationStateCreateInfo.Create();
//         rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_NONE;

//         // MULTISAMPLING
//         VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = VulkanUtil::PipelineMultisampleStateCreateInfo.Create();

//         // BLENDING
//         VkPipelineColorBlendAttachmentState colorBlendAttachmentState = VulkanUtil::PipelineColorBlendAttachmentState.Create();
//         VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = VulkanUtil::PipelineColorBlendStateCreateInfo.Create(colorBlendAttachmentState);

//         // DESCRIPTOR SET LAYOUT - UNIFORMS
//         VkDescriptorSetLayoutBinding projectionViewLayoutBinding = VulkanUtil::DescriptorSetLayoutBinding.CreateUniformForVertexStage(0);
//         VkDescriptorSetLayoutBinding textureLayoutBinding = VulkanUtil::DescriptorSetLayoutBinding.CreateTextureForFragmentStage(1);

//         // LAYOUT
//         VkPipelineLayout pipelineLayout = VulkanUtil::PipelineLayout.Create(device, );


//     }
// }

// #endif