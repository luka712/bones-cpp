
#if USE_WEBGPU 


#include "effects/wgpu/WebGPUBlurEffect.hpp"
#include "bns_framework.hpp"
#include "bns_webgpu_util.hpp"
#include "buffer_layout/BufferLayoutData.hpp"
#include "renderer/bns_webgpu_renderer.hpp"

namespace bns
{
    WebGPUBlurEffectImpl::WebGPUBlurEffectImpl(const Framework &framework)
        : WebGPUEffectImpl(framework)
    {
    }

    void WebGPUBlurEffectImpl::Initialize()
    {
        WebGPURenderer *renderer = static_cast<WebGPURenderer *>(m_framework.GetRenderer());
        m_device = renderer->GetDevice();
        m_vertexBuffer = CreateVertexBuffer();

        Vec2i bufferSize = m_framework.GetRenderer()->GetBufferSize();

        // since there is no parent call, create the source texture as well
        m_sourceTexture = m_framework
                              .GetTextureManager()
                              .CreateEmpty(bufferSize.X, bufferSize.Y,
                                           TextureUsage::CopyDst_TextureBinding_RenderAttachment,
                                           TextureFormat::BGRA_8_Unorm);

        Texture2D *midStepTexture = m_framework
                                    .GetTextureManager()
                                    .CreateEmpty(bufferSize.X, bufferSize.Y,
                                                 TextureUsage::CopyDst_TextureBinding_RenderAttachment,
                                                 TextureFormat::BGRA_8_Unorm);

        m_midStepTexture = static_cast<WebGPUTexture2D *>(midStepTexture);

        std::vector<WGPUBindGroupLayout> layouts = CreateBindGroupLayouts();
        std::vector<WGPUBindGroup> bindGroups = CreateBindGroups(layouts);

        CreateRenderPipeline(layouts);
    }

    std::vector<WGPUBindGroup> WebGPUBlurEffectImpl::CreateBindGroups(std::vector<WGPUBindGroupLayout> layouts)
    {

        std::vector<WGPUBindGroup> result = WebGPUEffectImpl::CreateBindGroups(layouts);

        // bind group layout can be used for both!
        if (m_sourceTextureBindGroupLayout == nullptr)
        {
            throw std::runtime_error("Texture bind group layout is null.");
        }

        if (m_midStepTexture == nullptr)
        {
            throw std::runtime_error("Vertical pass texture is null.");
        }

        m_midStepTextureBindGroup = CreateTextureBindGroup(*m_midStepTexture);

        // push bind group to result
        result.push_back(m_midStepTextureBindGroup);

        return result;
    }

    WGPURenderPipeline WebGPUBlurEffectImpl::CreatePipeline(WGPUShaderModule shaderModule, WGPUBindGroupLayout bindGroupLayout, std::string &fragmentMainName)
    {
        // Create pipeline layout. Here the global bind group layout is assigned.
        std::vector<WGPUBindGroupLayout> bindGroupLayouts = {bindGroupLayout};
        WGPUPipelineLayout layout = WebGPUUtil::PipelineLayout.Create(m_device, bindGroupLayouts);

        // 1 layout with 2 attributes
        BufferLayoutDescriptor bufferLayoutDescriptor;
        bufferLayoutDescriptor.StepMode = VertexStepMode::Vertex;
        bufferLayoutDescriptor.Stride = sizeof(f32) * 5; // x, y, z, u, v
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});

        std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
        vertexBufferLayouts.push_back(bufferLayoutDescriptor);

        size_t vertexBuffersLayoutCount;
        WGPUVertexBufferLayout *vertexBuffersLayout = WebGPUUtil::VertexBufferLayout.Create(vertexBufferLayouts, &vertexBuffersLayoutCount);

        // TODO: move to util
        WGPUVertexState vertexState;
        vertexState.nextInChain = nullptr;
        vertexState.entryPoint = "vs_main";
        vertexState.module = shaderModule;
        vertexState.bufferCount = vertexBuffersLayoutCount;
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
        std::string shaderSource = fileLoader.LoadFile(GetShaderPath());
        WGPUShaderModule shaderModule = WebGPUUtil::ShaderModule.Create(m_device, shaderSource, "blur_effect_sm");

        // Create pipeline layout. Here the global bind group layout is assigned.
        std::string fragFn = "fs_main_horizontal_pass";
        m_horizontalPassPipeline = CreatePipeline(shaderModule, m_sourceTextureBindGroupLayout, fragFn);
        std::string verexFn = "fs_main_vertical_pass";
        m_verticalPassPipeline = CreatePipeline(shaderModule, m_sourceTextureBindGroupLayout, verexFn);

        // release resources that are no longer needed
        wgpuShaderModuleRelease(shaderModule);

        // return nullptr as it is not used, m_horizontalPassPipeline and m_verticalPassPipeline are set
        return nullptr;
    }

    void WebGPUBlurEffectImpl::Draw(void *destinationTexture)
    {
        WebGPURenderer *renderer = static_cast<WebGPURenderer *>(m_framework.GetRenderer());
        WGPUDevice device = renderer->GetDevice();
        WGPUQueue queue = renderer->GetQueue();

        // Create a render pass for the encoder.
        WGPUTexture wgpuDestTexture = static_cast<WGPUTexture>(destinationTexture);
        WGPUTextureView viewIntoDestinationTexture = wgpuTextureCreateView(wgpuDestTexture, nullptr);

        // RENDER TO VERTICAL PASS TEXTURE

        // Create a command encoder which can be used to submit GPU operations.
        WGPUCommandEncoder horizontalPassEncoder = WebGPUUtil::CommandEncoder.Create(device, "blur horizontal pass ce");

        // Create a render pass for the encoder.
        WGPUTextureView viewIntoVerticalPassTexture = m_midStepTexture->CreateView();

        // Horizontal pass render into texture binding of vertical pass
        WGPURenderPassColorAttachment horizontalPassColorAttachment = WebGPUUtil::RenderPassColorAttachment.Create(viewIntoVerticalPassTexture);
        WGPURenderPassDescriptor horizontalRenderPassDesc = WebGPUUtil::RenderPassDescriptor.Create(horizontalPassColorAttachment);
        WGPURenderPassEncoder horizontalRenderPass = wgpuCommandEncoderBeginRenderPass(horizontalPassEncoder, &horizontalRenderPassDesc);

        // Set the pipeline that will be used for this render pass.
        wgpuRenderPassEncoderSetPipeline(horizontalRenderPass, m_horizontalPassPipeline);
        wgpuRenderPassEncoderSetBindGroup(horizontalRenderPass, 0, m_sourceTextureBindGroup, 0, nullptr);
        size_t byteSize = sizeof(float) * 5 * 6; // 5 per vertex, 6 vertices
        wgpuRenderPassEncoderSetVertexBuffer(horizontalRenderPass, 0, m_vertexBuffer, 0, byteSize);
        wgpuRenderPassEncoderDraw(horizontalRenderPass, 6, 1, 0, 0);
        wgpuRenderPassEncoderEnd(horizontalRenderPass);

        WGPUCommandBufferDescriptor horizontalPassCommandBufferDesc;
        horizontalPassCommandBufferDesc.label = "blur horizontal pass";
        WGPUCommandBuffer horizontalPassCommandBuffer = wgpuCommandEncoderFinish(horizontalPassEncoder, &horizontalPassCommandBufferDesc);

        wgpuQueueSubmit(queue, 1, &horizontalPassCommandBuffer);

        // release created resources
        wgpuTextureViewRelease(viewIntoVerticalPassTexture);
        wgpuCommandEncoderRelease(horizontalPassEncoder);

        // Create a command encoder which can be used to submit GPU operations.
        WGPUCommandEncoder verticalPassEncoder = WebGPUUtil::CommandEncoder.Create(device, "blur vertical pass ce");

        WGPURenderPassColorAttachment verticalPassColorAttachment = WebGPUUtil::RenderPassColorAttachment.Create(viewIntoDestinationTexture);
        WGPURenderPassDescriptor renderPassDesc = WebGPUUtil::RenderPassDescriptor.Create(verticalPassColorAttachment);
        WGPURenderPassEncoder verticalRenderPass = wgpuCommandEncoderBeginRenderPass(verticalPassEncoder, &renderPassDesc);

        // Set the pipeline that will be used for this render pass.
        wgpuRenderPassEncoderSetPipeline(verticalRenderPass, m_verticalPassPipeline);
        wgpuRenderPassEncoderSetBindGroup(verticalRenderPass, 0, m_midStepTextureBindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetVertexBuffer(verticalRenderPass, 0, m_vertexBuffer, 0, byteSize);
        wgpuRenderPassEncoderDraw(verticalRenderPass, 6, 1, 0, 0);
        wgpuRenderPassEncoderEnd(verticalRenderPass);

        WGPUCommandBufferDescriptor verticalPassCommandBufferDesc;
        verticalPassCommandBufferDesc.label = "Effect";
        WGPUCommandBuffer verticalPassCommandBuffer = wgpuCommandEncoderFinish(verticalPassEncoder, &verticalPassCommandBufferDesc);

        wgpuQueueSubmit(queue, 1, &verticalPassCommandBuffer);

        // release created resources
        wgpuTextureViewRelease(viewIntoDestinationTexture);
        wgpuCommandEncoderRelease(verticalPassEncoder);
    }

} // namespace bns

#endif 