#include "sprite/wgpu/WebGPUSpritePipeline.hpp"
#include "util/wgpu/WebGPUBufferUtil.hpp"
#include "renderer/common/WebGPURenderPipelineUtil.hpp"
#include "util/WebGPUUtil.hpp"
#include "util/wgpu/WebGPUVertexBufferLayoutUtil.hpp"
#include "loaders/FileLoader.hpp"
#include "util/wgpu/WebGPUShaderModuleUtil.hpp"


namespace bns
{
    WebGPUSpritePipeline::WebGPUSpritePipeline(WGPURenderPipeline pipeline, WGPUBindGroup projectionViewBindGroup, WGPUBindGroup textureBindGroup)
        : m_pipeline(pipeline), m_projectionViewBindGroup(projectionViewBindGroup), m_textureBindGroup(textureBindGroup) {}

    // NOTE: STATIC FUNCTION
    WebGPUSpritePipeline *WebGPUSpritePipeline::Create(WGPUDevice device, WebGPUTexture2D *texture, WGPUBuffer projectionViewBuffer)
    {
        FileLoader fileLoader;
        std::string shaderSource = fileLoader.OpenFile("shaders/webgpu/sprite/sprite_shader.wgsl");
        WGPUShaderModule shaderModule = WebGPUShaderModuleUtil::Create(device, shaderSource, "Sprite Shader Module");

        WGPURenderPipelineDescriptor renderPipelineDescriptor;
        renderPipelineDescriptor.label = "Sprite Render Pipeline Descriptor";
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
        WGPUFragmentState fragmentState = WebGPUUtil::FragmentState.Create(shaderModule, colorTarget, "fs_main");
        renderPipelineDescriptor.fragment = &fragmentState;

        // Bind group layout for projection view matrix
        WGPUBindGroupLayoutEntry projectionViewBufferLayoutEntry = WebGPUUtil::BindGroupLayoutEntry.CreateBindGroupLayoutEntryForUniformBuffer(0, WGPUShaderStage_Vertex);
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
        WGPUBindGroupLayoutEntry bindGroupLayoutEntries[2] = {
            samplerLayoutEntry,
            textureLayoutEntry};
        WGPUBindGroupLayoutDescriptor textureBindGroupLayoutDescriptor = WebGPUUtil::BindGroupLayoutDescriptor.Create(bindGroupLayoutEntries, 2);
        WGPUBindGroupLayout textureBindGroupLayout = wgpuDeviceCreateBindGroupLayout(device, &textureBindGroupLayoutDescriptor);

        // merge layout to array.
        WGPUBindGroupLayout bindGroupLayouts[2] = {
            projectionViewBufferBindGroupLayout,
            textureBindGroupLayout};

        // TODO: move to util
        WGPUPipelineLayoutDescriptor pipelineLayoutDescriptor = WebGPUUtil::PipelineLayoutDescriptor.Create(&bindGroupLayouts[0], 2);
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

        // release resources that are no longer needed
        wgpuShaderModuleRelease(shaderModule);
        wgpuBindGroupLayoutRelease(projectionViewBufferBindGroupLayout);
        wgpuBindGroupLayoutRelease(textureBindGroupLayout);
        wgpuPipelineLayoutRelease(renderPipelineDescriptor.layout);
        wgpuTextureViewRelease(textureView);
        WebGPUVertexBufferLayoutUtil::Delete(layout, 1);

        return new WebGPUSpritePipeline(pipeline, projectionViewBindGroup, textureBindGroup);
    }
}