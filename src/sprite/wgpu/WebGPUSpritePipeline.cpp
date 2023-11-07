#include "sprite/wgpu/WebGPUSpritePipeline.hpp"
#include "renderer/common/WebGPURenderPipelineUtil.hpp"
#include "WebGPUUtil.hpp"
#include "util/WebGPUVertexBufferLayoutUtil.hpp"
#include "FileLoader.hpp"
#include "util/WebGPUShaderModuleUtil.hpp"
#include "lights/AmbientLight.hpp"
#include "lights/PointLight.hpp"

namespace bns
{
    WebGPUSpritePipeline::WebGPUSpritePipeline(
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
    WebGPUSpritePipeline *WebGPUSpritePipeline::Create(
        WGPUDevice device,
        WebGPUTexture2D *texture,
        WGPUBuffer projectionViewBuffer,
        WGPUBuffer brightnessThresholdBuffer,
        WGPUBuffer ambientLightBuffer,
        WGPUBuffer pointLightBuffer)
    {
        FileLoader fileLoader;
        std::string shaderSource = fileLoader.LoadFile("shaders/webgpu/sprite/sprite.wgsl", {
            { "##FORWARD_2D_NUM_OF_POINT_LIGHTS##", std::to_string(FORWARD_2D_NUM_OF_POINT_LIGHTS) }
        });
        WGPUShaderModule shaderModule = WebGPUShaderModuleUtil::Create(device, shaderSource, "Sprite Shader Module");

        WGPURenderPipelineDescriptor renderPipelineDescriptor;
        renderPipelineDescriptor.label = "Sprite Pipeline";
        renderPipelineDescriptor.nextInChain = nullptr;

        BufferLayoutDescriptor bufferLayoutDescriptor;
        bufferLayoutDescriptor.Step = StepMode::Vertex;
        bufferLayoutDescriptor.Stride = sizeof(f32) * FLOATS_PER_VERTEX;
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x4, 2, sizeof(f32) * 5});

        std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
        vertexBufferLayouts.push_back(bufferLayoutDescriptor);

        WGPUVertexBufferLayout *layout = WebGPUVertexBufferLayoutUtil::Create(vertexBufferLayouts);

        // TODO: move to util
        WGPUVertexState vertexState;
        vertexState.nextInChain = nullptr;
        vertexState.entryPoint = "vs_main";
        vertexState.module = shaderModule;
        vertexState.bufferCount = 1;
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
        WGPUBindGroupLayoutEntry projectionViewBufferLayoutEntry = WebGPUUtil::BindGroupLayoutEntry.CreateUniformBufferLayoutEntry(0, WGPUShaderStage_Vertex);
        WGPUBindGroupLayoutDescriptor projectionViewBufferLayoutDescriptor = WebGPUUtil::BindGroupLayoutDescriptor.Create(&projectionViewBufferLayoutEntry, 1);
        WGPUBindGroupLayout projectionViewBufferBindGroupLayout = wgpuDeviceCreateBindGroupLayout(device, &projectionViewBufferLayoutDescriptor);

        // Bind group layout for texture
        // Sampler
        WGPUSamplerBindingLayout samplerBindingLayout = {};
        samplerBindingLayout.type = WGPUSamplerBindingType_Filtering;
        WGPUBindGroupLayoutEntry samplerLayoutEntry = WebGPUUtil::BindGroupLayoutEntry.CreateBindGroupLayoutEntry(0, WGPUShaderStage_Fragment, samplerBindingLayout);

        // texture layout
        WGPUTextureBindingLayout textureBindingLayout = {};
        textureBindingLayout.sampleType = WGPUTextureSampleType_Float;
        textureBindingLayout.viewDimension = WGPUTextureViewDimension_2D;
        WGPUBindGroupLayoutEntry textureLayoutEntry = WebGPUUtil::BindGroupLayoutEntry.CreateBindGroupLayoutEntry(1, WGPUShaderStage_Fragment, textureBindingLayout);

        // bind group layout descriptor
        WGPUBindGroupLayoutEntry bindGroupLayoutEntries[3] = {
            samplerLayoutEntry,
            textureLayoutEntry,
        };
        WGPUBindGroupLayoutDescriptor textureBindGroupLayoutDescriptor = WebGPUUtil::BindGroupLayoutDescriptor.Create(bindGroupLayoutEntries, 2);
        WGPUBindGroupLayout textureBindGroupLayout = wgpuDeviceCreateBindGroupLayout(device, &textureBindGroupLayoutDescriptor);

        // brightness threshold layout
        WGPUBindGroupLayoutEntry brightnessLightsBindGroupLayoutEntries[3] = {
            WebGPUUtil::BindGroupLayoutEntry.CreateUniformBufferLayoutEntry(0, WGPUShaderStage_Fragment), // brightness threshold
            WebGPUUtil::BindGroupLayoutEntry.CreateUniformBufferLayoutEntry(1, WGPUShaderStage_Fragment), // ambient light
            WebGPUUtil::BindGroupLayoutEntry.CreateUniformBufferLayoutEntry(2, WGPUShaderStage_Fragment)  // point light
        };

        std::string brightnessLightsBindGroupLayoutLabel = "Brightness Lights Bind Group Layout";
        WGPUBindGroupLayoutDescriptor brightnessLightsBindGroupLayoutDescriptor = WebGPUUtil::BindGroupLayoutDescriptor.Create(
            &brightnessLightsBindGroupLayoutEntries[0],
            3,
            brightnessLightsBindGroupLayoutLabel);
        WGPUBindGroupLayout brightnessLightsBindGroupLayout = wgpuDeviceCreateBindGroupLayout(device, &brightnessLightsBindGroupLayoutDescriptor);

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

        // Projection view uniform buffer
        WGPUBindGroupEntry projectionViewBindGroupEntry =
            WebGPUUtil::BindGroupEntry.Create(0, projectionViewBuffer, sizeof(f32) * 16);
        WGPUBindGroupDescriptor projectionViewBindGroupDescriptor = WebGPUUtil::BindGroupDescriptor.Create(projectionViewBufferBindGroupLayout, &projectionViewBindGroupEntry, 1);
        WGPUBindGroup projectionViewBindGroup = wgpuDeviceCreateBindGroup(device, &projectionViewBindGroupDescriptor);

        // Sampler/Texture bind group
        WGPUTextureViewDescriptor textureViewDescriptor = WebGPUUtil::TextureViewDescriptor.Create();
        WGPUTextureView textureView = wgpuTextureCreateView(texture->Texture, &textureViewDescriptor);

        WGPUBindGroupEntry textureBindGroupEntries[2];
        textureBindGroupEntries[0] = WebGPUUtil::BindGroupEntry.Create(0, texture->Sampler);
        textureBindGroupEntries[1] = WebGPUUtil::BindGroupEntry.Create(1, textureView);
        WGPUBindGroupDescriptor textureBindGroupDescriptor = WebGPUUtil::BindGroupDescriptor.Create(textureBindGroupLayout, textureBindGroupEntries, 2);
        WGPUBindGroup textureBindGroup = wgpuDeviceCreateBindGroup(device, &textureBindGroupDescriptor);

        // Brightness threshold bind group
        WGPUBindGroupEntry brightnessThresholdBindGroupEntries[3] = {
            WebGPUUtil::BindGroupEntry.Create(0, brightnessThresholdBuffer, sizeof(f32)),
            WebGPUUtil::BindGroupEntry.Create(1, ambientLightBuffer, sizeof(AmbientLight)),
            WebGPUUtil::BindGroupEntry.Create(2, pointLightBuffer, sizeof(PointLight) * FORWARD_2D_NUM_OF_POINT_LIGHTS)};

        auto brightnessThresholdBindGroupDescriptor = WebGPUUtil::BindGroupDescriptor.Create(
            brightnessLightsBindGroupLayout,
            &brightnessThresholdBindGroupEntries[0],
            3);
        auto brightnessThresholdBindGroup = wgpuDeviceCreateBindGroup(device, &brightnessThresholdBindGroupDescriptor);

        // release resources that are no longer needed
        wgpuShaderModuleRelease(shaderModule);
        wgpuBindGroupLayoutRelease(projectionViewBufferBindGroupLayout);
        wgpuBindGroupLayoutRelease(textureBindGroupLayout);
        wgpuBindGroupLayoutRelease(brightnessLightsBindGroupLayout);
        wgpuPipelineLayoutRelease(renderPipelineDescriptor.layout);
        wgpuTextureViewRelease(textureView);
        WebGPUVertexBufferLayoutUtil::Delete(layout, 1);

        return new WebGPUSpritePipeline(pipeline, projectionViewBindGroup, textureBindGroup, brightnessThresholdBindGroup);
    }
}
