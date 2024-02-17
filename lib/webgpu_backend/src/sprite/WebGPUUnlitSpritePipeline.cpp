#if USE_WEBGPU

#include "sprite/WebGPUUnlitSpritePipeline.hpp"
#include "bns_webgpu_util.hpp"
#include "loaders/bns_file_loader.hpp"

namespace bns
{
    WebGPUUnlitSpritePipeline::WebGPUUnlitSpritePipeline(
        WGPURenderPipeline pipeline,
        WGPUBindGroup projectionViewBindGroup,
        WGPUBindGroup textureBindGroup,
        WGPUBindGroup brightnessThresholdBindGroup)
        : m_pipeline(pipeline),
          m_projectionViewBindGroup(projectionViewBindGroup),
          m_sourceTextureBindGroup(textureBindGroup),
          m_brightnessThresholdBindGroup(brightnessThresholdBindGroup)

    {
        InstanceIndex = 0;
    }

    // NOTE: STATIC FUNCTION
    WGPUBindGroup WebGPUUnlitSpritePipeline::CreateProjectionViewBindGroup(WGPUDevice& device,
                                                                           WGPUBindGroupLayout& projectionViewBufferBindGroupLayout,
                                                                           WGPUBuffer& projectionViewBuffer)
    {
        // Projection view uniform buffer
        WGPUBindGroupEntry projectionViewBindGroupEntry =
            WebGPUUtil::BindGroupEntry.Create(0, projectionViewBuffer, sizeof(f32) * 16);
        WGPUBindGroupDescriptor projectionViewBindGroupDescriptor = WebGPUUtil::BindGroupDescriptor.Create(projectionViewBufferBindGroupLayout, &projectionViewBindGroupEntry, 1);
        return wgpuDeviceCreateBindGroup(device, &projectionViewBindGroupDescriptor);
    }

    // NOTE: STATIC FUNCTION
    WGPUBindGroup WebGPUUnlitSpritePipeline::CreateTextureBindGroup(
        WGPUDevice& device,
        WGPUBindGroupLayout& textureBindGroupLayout,
        WebGPUTexture2D *texture)
    {
        // Sampler/Texture bind group
        WGPUTextureViewDescriptor textureViewDescriptor = WebGPUUtil::TextureViewDescriptor.Create();
        WGPUTextureView textureView = wgpuTextureCreateView(texture->Texture, &textureViewDescriptor);

        WGPUBindGroupEntry textureBindGroupEntries[2];
        textureBindGroupEntries[0] = WebGPUUtil::BindGroupEntry.Create(0, texture->Sampler);
        textureBindGroupEntries[1] = WebGPUUtil::BindGroupEntry.Create(1, textureView);
        WGPUBindGroupDescriptor textureBindGroupDescriptor = WebGPUUtil::BindGroupDescriptor.Create(textureBindGroupLayout, textureBindGroupEntries, 2);

        WGPUBindGroup bindGroup = wgpuDeviceCreateBindGroup(device, &textureBindGroupDescriptor);
        wgpuTextureViewRelease(textureView);
        return bindGroup;
    }

    // NOTE: STATIC FUNCTION
    WGPUBindGroup WebGPUUnlitSpritePipeline::CreateBrightnessThresholdBindGroup(WGPUDevice& device,
                                                                                WGPUBindGroupLayout& brightnessThresholdBindGroupLayout,
                                                                                WGPUBuffer& brightnessThresholdBuffer)
    {
        // Brightness threshold bind group
        WGPUBindGroupEntry brightnessThresholdBindGroupEntries[3] = {
            WebGPUUtil::BindGroupEntry.Create(0, brightnessThresholdBuffer, sizeof(f32))};

        WGPUBindGroupDescriptor brightnessThresholdBindGroupDescriptor = WebGPUUtil::BindGroupDescriptor.Create(
            brightnessThresholdBindGroupLayout,
            &brightnessThresholdBindGroupEntries[0],
            1);
        
        return wgpuDeviceCreateBindGroup(device, &brightnessThresholdBindGroupDescriptor);
    }

    // NOTE: STATIC FUNCTION
    WebGPUUnlitSpritePipeline *WebGPUUnlitSpritePipeline::Create(
        WGPUDevice device,
        WebGPUTexture2D *texture,
        WGPUBuffer projectionViewBuffer,
        WGPUBuffer brightnessThresholdBuffer)
    {
        FileLoader fileLoader;
        std::string shaderSource = fileLoader.LoadFile("shaders/webgpu/sprite/unlit_sprite.wgsl");
        WGPUShaderModule shaderModule = WebGPUShaderModuleUtil::Create(device, shaderSource, "Sprite Shader Module");

        WGPURenderPipelineDescriptor renderPipelineDescriptor;
        renderPipelineDescriptor.label = "Sprite Pipeline";
        renderPipelineDescriptor.nextInChain = nullptr;

        BufferLayoutDescriptor bufferLayoutDescriptor;
        bufferLayoutDescriptor.Step = VertexStepMode::Vertex;
        bufferLayoutDescriptor.Stride = sizeof(f32) * FLOATS_PER_VERTEX;
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x4, 2, sizeof(f32) * 5});

        std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
        vertexBufferLayouts.push_back(bufferLayoutDescriptor);

        // Should be 1, since there is only 1 vertex buffer layout descriptor
        size_t vertexBufferLayoutCount = 0;
        WGPUVertexBufferLayout *layout = WebGPUVertexBufferLayoutUtil::Create(vertexBufferLayouts, &vertexBufferLayoutCount);


        // TODO: move to util
        WGPUVertexState vertexState;
        vertexState.nextInChain = nullptr;
        vertexState.entryPoint = "vs_main";
        vertexState.module = shaderModule;
        vertexState.bufferCount = vertexBufferLayoutCount;
        vertexState.buffers = layout;
        vertexState.constantCount = 0;
        renderPipelineDescriptor.vertex = vertexState;

        // Fragment state
        WGPUBlendState blend = {};
        blend.color.operation = WGPUBlendOperation_Add;
        blend.color.srcFactor = WGPUBlendFactor_One;
        blend.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
        blend.alpha.operation = WGPUBlendOperation_Add;
        blend.alpha.srcFactor = WGPUBlendFactor_One;
        blend.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;

        // default color target state
        WGPUColorTargetState colorTarget = {};
        colorTarget.nextInChain = nullptr;
        colorTarget.format = WGPUTextureFormat_BGRA8Unorm;
        colorTarget.blend = &blend;
        colorTarget.writeMask = WGPUColorWriteMask_All;
        std::string fragFn = "fs_main";

        // 2 color target states, first one for the screen, second one for the bloom/brightness texture
        // Here both color target states can be same, there is no difference.
        WGPUColorTargetState colorTargetsStates[2];
        colorTargetsStates[0] = colorTarget;
        colorTargetsStates[1] = colorTarget;
        WGPUFragmentState fragmentState = WebGPUUtil::FragmentState.Create(shaderModule, &colorTargetsStates[0], 2, fragFn);
        renderPipelineDescriptor.fragment = &fragmentState;

        // Bind group layout for projection view matrix
        std::vector<WebGPUBindGroupLayoutEntry> bindGroupLayoutEntries = {
            WebGPUBindGroupLayoutEntry::CreateUniformBufferLayoutEntry(0, ShaderType::Vertex)
        };
        WGPUBindGroupLayout projectionViewBufferBindGroupLayout = WebGPUUtil::BindGroupLayout.Create(device, bindGroupLayoutEntries, "Projection View Bind Group Layout");

        // Bind group layout for texture
        bindGroupLayoutEntries = {
            WebGPUBindGroupLayoutEntry::CreateSamplerLayoutEntry(0, ShaderType::Fragment),
			WebGPUBindGroupLayoutEntry::CreateTextureLayoutEntry(1, ShaderType::Fragment)
		};
        WGPUBindGroupLayout textureBindGroupLayout = WebGPUUtil::BindGroupLayout.Create(device, bindGroupLayoutEntries, "Texture Bind Group Layout");

        // brightness threshold layout
        bindGroupLayoutEntries = {
            WebGPUBindGroupLayoutEntry::CreateUniformBufferLayoutEntry(0, ShaderType::Fragment)
        };
        WGPUBindGroupLayout brightnessLightsBindGroupLayout = WebGPUUtil::BindGroupLayout.Create(device, bindGroupLayoutEntries, "Brightness Threshold Bind Group Layout");

        // merge layout to array.
        WGPUBindGroupLayout bindGroupLayouts[3] = {
            projectionViewBufferBindGroupLayout,
            textureBindGroupLayout,
            brightnessLightsBindGroupLayout};

        // TODO: move to util
        WGPUPipelineLayoutDescriptor pipelineLayoutDescriptor = WebGPUUtil::PipelineLayoutDescriptor.Create(&bindGroupLayouts[0], 3);
        renderPipelineDescriptor.layout = wgpuDeviceCreatePipelineLayout(device, &pipelineLayoutDescriptor);

        renderPipelineDescriptor.depthStencil = nullptr;

        renderPipelineDescriptor.multisample.nextInChain = nullptr;
        renderPipelineDescriptor.multisample.count = 1;
        renderPipelineDescriptor.multisample.mask = 0xFFFFFFFF;
        renderPipelineDescriptor.multisample.alphaToCoverageEnabled = false;

        renderPipelineDescriptor.primitive.nextInChain = nullptr;
        renderPipelineDescriptor.primitive.frontFace = WGPUFrontFace_CCW;
        renderPipelineDescriptor.primitive.cullMode = WGPUCullMode_None;
        renderPipelineDescriptor.primitive.topology = WGPUPrimitiveTopology_TriangleList;
        renderPipelineDescriptor.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;

        WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(device, &renderPipelineDescriptor);

        // Create bind groups
        WGPUBindGroup projectionViewBindGroup = CreateProjectionViewBindGroup(device, projectionViewBufferBindGroupLayout, projectionViewBuffer);
        WGPUBindGroup textureBindGroup = CreateTextureBindGroup(device, textureBindGroupLayout, texture);
        WGPUBindGroup brightnessThresholdBindGroup = CreateBrightnessThresholdBindGroup(device, brightnessLightsBindGroupLayout, brightnessThresholdBuffer);

        // release resources that are no longer needed
        wgpuShaderModuleRelease(shaderModule);
        wgpuBindGroupLayoutRelease(projectionViewBufferBindGroupLayout);
        wgpuBindGroupLayoutRelease(textureBindGroupLayout);
        wgpuBindGroupLayoutRelease(brightnessLightsBindGroupLayout);
        wgpuPipelineLayoutRelease(renderPipelineDescriptor.layout);
        WebGPUVertexBufferLayoutUtil::Delete(layout, vertexBufferLayoutCount);

        return new WebGPUUnlitSpritePipeline(pipeline, projectionViewBindGroup, textureBindGroup, brightnessThresholdBindGroup);
    }
}

#endif
