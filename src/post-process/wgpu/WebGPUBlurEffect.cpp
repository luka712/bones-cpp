#include "post-process/wgpu/WebGPUBlurEffect.hpp"
#include "Framework.hpp"
#include "util/WebGPUUtil.hpp"
#include "buffer-layout/BufferLayoutData.hpp"

namespace bns
{
    WebGPUBlurEffectImpl::WebGPUBlurEffectImpl(const Framework &framework)
        : WebGPUEffectImpl(framework)
    {
    }

    void WebGPUBlurEffectImpl::Initialize()
    {
        m_device = m_framework.Context.WebGPUDevice;
        m_vertexBuffer = CreateVertexBuffer();

        Vec2u bufferSize = m_framework.GetRenderer().GetBufferSize();
        Texture2D *horTexture = m_framework
                                    .GetTextureFactory()
                                    .CreateEmpty(bufferSize.X, bufferSize.Y,
                                                 TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT,
                                                 TextureFormat::BGRA_8_Unorm);
        Texture2D *verTexture = m_framework
                                    .GetTextureFactory()
                                    .CreateEmpty(bufferSize.X, bufferSize.Y,
                                                 TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT,
                                                 TextureFormat::BGRA_8_Unorm);

        m_horizontalPassTexture = static_cast<WebGPUTexture2D *>(horTexture);
        m_verticalPassTexture = static_cast<WebGPUTexture2D *>(verTexture);

        std::vector<WGPUBindGroupLayout> layouts = CreateBindGroupLayouts();
        std::vector<WGPUBindGroup> bindGroups = CreateBindGroups(layouts);

        CreateRenderPipeline(layouts);
    }

    std::vector<WGPUBindGroup> WebGPUBlurEffectImpl::CreateBindGroups(std::vector<WGPUBindGroupLayout> layouts)
    {
        std::vector<WGPUBindGroup> result;

        // bind group layout can be used for both!
        if (m_sourceTextureBindGroupLayout == nullptr)
        {
            throw std::runtime_error("Texture bind group layout is null.");
        }

        if (m_horizontalPassTexture == nullptr)
        {
            throw std::runtime_error("Horizontal pass texture is null.");
        }

        if (m_verticalPassTexture == nullptr)
        {
            throw std::runtime_error("Vertical pass texture is null.");
        }

        // HORIZONTAL
        WGPUBindGroupEntry horizontalTexBindGroupEntries[2];
        horizontalTexBindGroupEntries[0] = WebGPUUtil::BindGroupEntry.Create(0, m_horizontalPassTexture->Sampler);
        horizontalTexBindGroupEntries[1] = WebGPUUtil::BindGroupEntry.Create(1, m_horizontalPassTexture->CreateView());

        // Create bind group
        WGPUBindGroupDescriptor bindGroupDesc = WebGPUUtil::BindGroupDescriptor.Create(m_sourceTextureBindGroupLayout, horizontalTexBindGroupEntries, 2);
        m_horizontalPassTextureBindGroup = wgpuDeviceCreateBindGroup(m_device, &bindGroupDesc);

        // push bind group to result
        result.push_back(m_horizontalPassTextureBindGroup);

        // VERTICAL
        WGPUBindGroupEntry verticalTexBindGroupEntries[2];
        verticalTexBindGroupEntries[0] = WebGPUUtil::BindGroupEntry.Create(0, m_verticalPassTexture->Sampler);
        verticalTexBindGroupEntries[1] = WebGPUUtil::BindGroupEntry.Create(1, m_verticalPassTexture->CreateView());

        // Create bind group
        bindGroupDesc = WebGPUUtil::BindGroupDescriptor.Create(m_sourceTextureBindGroupLayout, verticalTexBindGroupEntries, 2);
        m_verticalPassTextureBindGroup = wgpuDeviceCreateBindGroup(m_device, &bindGroupDesc);

        // push bind group to result
        result.push_back(m_verticalPassTextureBindGroup);

        return result;
    }

    WGPURenderPipeline WebGPUBlurEffectImpl::CreatePipeline(WGPUShaderModule shaderModule, WGPUBindGroupLayout bindGroupLayout, std::string fragmentMainName)
    {
        // Create pipeline layout. Here the global bind group layout is assigned.
        WGPUPipelineLayoutDescriptor desc = WebGPUPipelineLayoutDescriptorUtil::Create(&bindGroupLayout, 1);
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
        WGPUFragmentState fragmentState = WebGPUFragmentStateUtil::Create(shaderModule, colorTarget, fragmentMainName);

        // WGPUDepthStencilState depthStencilState = WebGPUDepthStencilStateUtil::Create();

        WGPURenderPipelineDescriptor renderPipelineDescriptor = WebGPUUtil::RenderPipelineDescriptor.Create(
            layout,
            vertexState,
            fragmentState,
            nullptr,
            WGPUPrimitiveTopology::WGPUPrimitiveTopology_TriangleList,
            WGPUCullMode::WGPUCullMode_None,
            "PostProcessRenderPipeline");

        WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(m_device, &renderPipelineDescriptor);

        wgpuPipelineLayoutRelease(layout);
        WebGPUUtil::VertexBufferLayout.Delete(vertexBuffersLayout, 1);

        return pipeline;
    }

    WGPURenderPipeline WebGPUBlurEffectImpl::CreateRenderPipeline(std::vector<WGPUBindGroupLayout> bindGroupLayouts)
    {

        FileLoader fileLoader;
        std::string shaderSource = fileLoader.OpenFile(GetShaderPath());
        WGPUShaderModule shaderModule = WebGPUUtil::ShaderModule.Create(m_device, shaderSource, "blur_effect_sm");

        // Create pipeline layout. Here the global bind group layout is assigned.
        m_horizontalPassPipeline = CreatePipeline(shaderModule, m_sourceTextureBindGroupLayout, "fs_main_horizontal_pass");
        m_verticalPassPipeline = CreatePipeline(shaderModule, m_sourceTextureBindGroupLayout, "fs_main_vertical_pass");

        // release resources that are no longer needed
        wgpuShaderModuleRelease(shaderModule);

        // return nullptr as it is not used, m_horizontalPassPipeline and m_verticalPassPipeline are set
        return nullptr;
    }

    void WebGPUBlurEffectImpl::Draw(void *destinationTexture)
    {
        WGPUDevice device = m_framework.Context.WebGPUDevice;

        // RENDER TO VERTICAL PASS TEXTURE

        // Create a command encoder which can be used to submit GPU operations.
        WGPUCommandEncoder horizontalPassEncoder = WebGPUUtil::CommandEncoder.Create(device, "blur horizontal pass ce");

        // Create a render pass for the encoder.
        WGPUTextureView viewIntoVerticalPassTexture = m_verticalPassTexture->CreateView();

        // Horizontal pass render into texture binding of vertical pass
        WGPURenderPassColorAttachment horizontalPassColorAttachment = WebGPUUtil::RenderPassColorAttachment.Create(viewIntoVerticalPassTexture);
        WGPURenderPassDescriptor horizontalRenderPassDesc = WebGPUUtil::RenderPassDescriptor.Create(horizontalPassColorAttachment);
        WGPURenderPassEncoder horizontalRenderPass = wgpuCommandEncoderBeginRenderPass(horizontalPassEncoder, &horizontalRenderPassDesc);

        // Set the pipeline that will be used for this render pass.
        wgpuRenderPassEncoderSetPipeline(horizontalRenderPass, m_horizontalPassPipeline);
        wgpuRenderPassEncoderSetBindGroup(horizontalRenderPass, 0, m_horizontalPassTextureBindGroup, 0, nullptr);
        size_t byteSize = sizeof(float) * 5 * 6; // 5 per vertex, 6 vertices
        wgpuRenderPassEncoderSetVertexBuffer(horizontalRenderPass, 0, m_vertexBuffer, 0, byteSize);
        wgpuRenderPassEncoderDraw(horizontalRenderPass, 6, 1, 0, 0);
        wgpuRenderPassEncoderEnd(horizontalRenderPass);

        WGPUCommandBufferDescriptor horizontalPassCommandBufferDesc;
        horizontalPassCommandBufferDesc.label = "blur horizontal pass";
        WGPUCommandBuffer horizontalPassCommandBuffer = wgpuCommandEncoderFinish(horizontalPassEncoder, &horizontalPassCommandBufferDesc);

        wgpuQueueSubmit(m_framework.Context.WebGPUQueue, 1, &horizontalPassCommandBuffer);

        // release created resources
        wgpuTextureViewRelease(viewIntoVerticalPassTexture);
        wgpuCommandEncoderRelease(horizontalPassEncoder);



        // Create a command encoder which can be used to submit GPU operations.
        WGPUCommandEncoder verticalPassEncoder = WebGPUUtil::CommandEncoder.Create(device, "blur vertical pass ce");

        // Create a render pass for the encoder.
        WGPUTexture wgpuDestTexture = static_cast<WGPUTexture>(destinationTexture);
        WGPUTextureView viewIntoDestinationTexture = wgpuTextureCreateView(wgpuDestTexture, nullptr);

        WGPURenderPassColorAttachment verticalPassColorAttachment = WebGPUUtil::RenderPassColorAttachment.Create(viewIntoDestinationTexture);
        WGPURenderPassDescriptor renderPassDesc = WebGPUUtil::RenderPassDescriptor.Create(verticalPassColorAttachment);
        WGPURenderPassEncoder verticalRenderPass = wgpuCommandEncoderBeginRenderPass(verticalPassEncoder, &renderPassDesc);

        // Set the pipeline that will be used for this render pass.
        wgpuRenderPassEncoderSetPipeline(verticalRenderPass, m_verticalPassPipeline);
        wgpuRenderPassEncoderSetBindGroup(verticalRenderPass, 0, m_verticalPassTextureBindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetVertexBuffer(verticalRenderPass, 0, m_vertexBuffer, 0, byteSize);
        wgpuRenderPassEncoderDraw(verticalRenderPass, 6, 1, 0, 0);
        wgpuRenderPassEncoderEnd(verticalRenderPass);

        WGPUCommandBufferDescriptor verticalPassCommandBufferDesc;
        verticalPassCommandBufferDesc.label = "Effect";
        WGPUCommandBuffer verticalPassCommandBuffer = wgpuCommandEncoderFinish(verticalPassEncoder, &verticalPassCommandBufferDesc);

        wgpuQueueSubmit(m_framework.Context.WebGPUQueue, 1, &verticalPassCommandBuffer);

        // release created resources
        wgpuTextureViewRelease(viewIntoDestinationTexture);
        wgpuCommandEncoderRelease(verticalPassEncoder);
    }

} // namespace bns
