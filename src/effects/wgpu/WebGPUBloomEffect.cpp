#include "effects/wgpu/WebGPUBloomEffect.hpp"
#include "util/WebGPUUtil.hpp"
#include "Framework.hpp"

namespace bns
{
    WebGPUBloomEffectImpl::WebGPUBloomEffectImpl(const Framework &framework)
        : WebGPUEffectImpl(framework), m_blurEffect(framework)
    {
        m_brightnessTexture = nullptr;
        m_brightnessTextureBindGroup = nullptr;
        BrightnessBlurPasses = 3;
    }

    void WebGPUBloomEffectImpl::Initialize()
    {
        Vec2u bufferSize = m_framework.GetRenderer()->GetBufferSize();
        Texture2D *texture = m_framework
                                    .GetTextureManager()
                                    .CreateEmpty(bufferSize.X, bufferSize.Y,
                                                 TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT,
                                                 TextureFormat::BGRA_8_Unorm);

        m_brightnessTexture = static_cast<WebGPUTexture2D *>(texture);
        
        WebGPUEffectImpl::Initialize();
        m_blurEffect.Initialize();
        m_blurEffect.SetSourceTexture(m_brightnessTexture);
    }

    WGPUBindGroup WebGPUBloomEffectImpl::CreateBrightnessTextureBindGroup()
    {
        // there is no texture, it cannot be created
        if (m_brightnessTexture == nullptr)
        {
            throw std::runtime_error("Cannot create brightness texture bind group because m_brightnessTexture is null.");
            return nullptr;
        }

        // if there is already a bind group, release it as it is changed
        if (m_brightnessTextureBindGroup != nullptr)
        {
            wgpuBindGroupRelease(m_brightnessTextureBindGroup);
        }

        WGPUBindGroupEntry bindGroupEntries[2];

        // sampler entry
        WebGPUTexture2D *webGPUTexture2D = static_cast<WebGPUTexture2D *>(m_brightnessTexture);
        bindGroupEntries[0] = WebGPUUtil::BindGroupEntry.Create(0, webGPUTexture2D->Sampler);

        // texture entry
        WGPUTextureView view = webGPUTexture2D->CreateView();
        bindGroupEntries[1] = WebGPUUtil::BindGroupEntry.Create(1, view);

        // Create bind group
        std::string bindGroupName = "Brightness Texture Bind Group";
        WGPUBindGroupDescriptor bindGroupDesc = WebGPUUtil::BindGroupDescriptor.Create(m_sourceTextureBindGroupLayout,
                                                                                       bindGroupEntries,
                                                                                       2,
                                                                                       bindGroupName);
        WGPUBindGroup bindGroup = wgpuDeviceCreateBindGroup(m_device, &bindGroupDesc);

        m_brightnessTextureBindGroup = bindGroup;

        return bindGroup;
    }

    void WebGPUBloomEffectImpl::SetBrightnessTexture(WebGPUTexture2D *brightnessTexture)
    {
        m_brightnessTexture = brightnessTexture;
        // m_brightnessTextureBindGroup is assigned by default in CreateBindGroupLayouts.
        CreateBrightnessTextureBindGroup();
    }

    std::vector<WGPUBindGroup> WebGPUBloomEffectImpl::CreateBindGroups(std::vector<WGPUBindGroupLayout> bindGroupLayouts)
    {
        std::vector<WGPUBindGroup> result = WebGPUEffectImpl::CreateBindGroups(bindGroupLayouts);

        // m_brightnessTextureBindGroup is assigned by default in CreateBindGroupLayouts.
        WGPUBindGroup brightnessTextureBindGroup = CreateBrightnessTextureBindGroup();
        if (brightnessTextureBindGroup != nullptr)
        {
            result.push_back(brightnessTextureBindGroup);
        }

        return result;
    }

WGPURenderPipeline WebGPUBloomEffectImpl::CreateRenderPipeline(std::vector<WGPUBindGroupLayout> layouts)
{
    FileLoader fileLoader;
    std::string shaderSource = fileLoader.LoadFile(GetShaderPath());
    WGPUShaderModule shaderModule = WebGPUUtil::ShaderModule.Create(m_device, shaderSource);

    // Create pipeline layout. Here the global bind group layout is assigned.
    std::vector<WGPUBindGroupLayout> _layouts = {
        m_sourceTextureBindGroupLayout,
        m_sourceTextureBindGroupLayout
    };
    WGPUPipelineLayoutDescriptor desc = WebGPUPipelineLayoutDescriptorUtil::Create(_layouts.data(), _layouts.size());
    WGPUPipelineLayout layout = wgpuDeviceCreatePipelineLayout(m_device, &desc);

    // 1 layout with 2 attributes
    BufferLayoutDescriptor bufferLayoutDescriptor;
    bufferLayoutDescriptor.Step = StepMode::Vertex;
    bufferLayoutDescriptor.Stride = sizeof(f32) * 5; // x, y, z, u, v
    bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
    bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});

    std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
    vertexBufferLayouts.push_back(bufferLayoutDescriptor);

    WGPUVertexBufferLayout *vertexBuffersLayout = WebGPUUtil::VertexBufferLayout.Create(vertexBufferLayouts);

    // TODO: move to util
    WGPUVertexState vertexState;
    vertexState.nextInChain = nullptr;
    vertexState.entryPoint = "vs_main";
    vertexState.module = shaderModule;
    vertexState.bufferCount = 1;
    vertexState.buffers = vertexBuffersLayout;
    vertexState.constantCount = 0;

    // Fragment state
    WGPUBlendState blend = WebGPUUtil::BlendState.Create();

    // default color target state
    // TODO: move to util
    WGPUColorTargetState colorTarget = {};
    colorTarget.nextInChain = nullptr;
    colorTarget.format = WGPUTextureFormat_BGRA8Unorm;
    colorTarget.blend = &blend;
    colorTarget.writeMask = WGPUColorWriteMask_All;
    std::string fragFn = "fs_main";
    WGPUFragmentState fragmentState = WebGPUUtil::FragmentState.Create(shaderModule, colorTarget, fragFn);

    // WGPUDepthStencilState depthStencilState = WebGPUDepthStencilStateUtil::Create();

    WGPURenderPipelineDescriptor renderPipelineDescriptor = WebGPURenderPipelineDescriptorUtil::Create(
        layout,
        vertexState,
        fragmentState,
        nullptr,
        WGPUPrimitiveTopology::WGPUPrimitiveTopology_TriangleList,
        WGPUCullMode::WGPUCullMode_None,
        "PostProcessRenderPipeline");
    WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(m_device, &renderPipelineDescriptor);

    // release resources that are no longer needed
    wgpuShaderModuleRelease(shaderModule);
    wgpuPipelineLayoutRelease(renderPipelineDescriptor.layout);
    WebGPUVertexBufferLayoutUtil::Delete(vertexBuffersLayout, 1);

    return pipeline;
};


    void WebGPUBloomEffectImpl::Draw(void *texture)
    {
        for(u32 i = 0; i < BrightnessBlurPasses; i++)
        {
            m_blurEffect.Draw(m_brightnessTexture->Texture);
        }

        WGPUDevice device = m_framework.Context.WebGPUDevice;
        WGPUQueue queue = m_framework.Context.WebGPUQueue;

        // Create a command encoder which can be used to submit GPU operations.
        WGPUCommandEncoderDescriptor desc;
        desc.nextInChain = nullptr;
        desc.label = "Bloom Effect Command Encoder";
        WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, &desc);

        // Create a render pass for the encoder.
        WGPUTexture wgpuTexture = static_cast<WGPUTexture>(texture);
        WGPUTextureView wgpuTextureView = wgpuTextureCreateView(wgpuTexture, nullptr);

        WGPURenderPassColorAttachment colorAttachment = WebGPUUtil::RenderPassColorAttachment.Create(wgpuTextureView);
        WGPURenderPassDescriptor renderPassDesc = WebGPUUtil::RenderPassDescriptor.Create(colorAttachment);
        WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDesc);

        // Set the pipeline that will be used for this render pass.
        wgpuRenderPassEncoderSetPipeline(renderPass, m_pipeline);

        // Set bind groups
        wgpuRenderPassEncoderSetBindGroup(renderPass, 0, m_sourceTextureBindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetBindGroup(renderPass, 1, m_brightnessTextureBindGroup, 0, nullptr);

        // Set buffers
        size_t byteSize = sizeof(float) * 5 * 6; // 5 per vertex, 6 vertices
        wgpuRenderPassEncoderSetVertexBuffer(renderPass, 0, m_vertexBuffer, 0, byteSize);

        wgpuRenderPassEncoderDraw(renderPass, 6, 1, 0, 0);
        wgpuRenderPassEncoderEnd(renderPass);

        WGPUCommandBufferDescriptor commandBufferDesc;
        commandBufferDesc.label = "Blooom Effect Command Buffer";
        WGPUCommandBuffer commandBuffer = wgpuCommandEncoderFinish(encoder, &commandBufferDesc);

        wgpuQueueSubmit(queue, 1, &commandBuffer);

        // release created resources
        wgpuTextureViewRelease(wgpuTextureView);
        wgpuCommandEncoderRelease(encoder);
    }

} // namespace bns
