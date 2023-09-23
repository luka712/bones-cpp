#include "post-process/wgpu/WebGPUPostProcessEffect.hpp"
#include "textures/wgpu/WebGPUTexture2D.hpp"
#include "Framework.hpp"
#include "util/wgpu/WebGPURenderPassColorAttachmentUtil.hpp"
#include "util/wgpu/WebGPURenderPassDescriptorUtil.hpp"
#include "util/wgpu/WebGPUBufferUtil.hpp"
#include "util/wgpu/WebGPUBindGroupLayoutEntryUtil.hpp"
#include "util/wgpu/WebGPUBindGroupLayoutDescriptorUtil.hpp"
#include "util/wgpu/WebGPUBindGroupEntryUtil.hpp"
#include "util/wgpu/WebGPUBindGroupDescriptorUtil.hpp"
#include "util/wgpu/WebGPUPipelineLayoutDescriptorUtil.hpp"
#include "util/wgpu/WebGPUShaderModuleUtil.hpp"
#include "util/wgpu/WebGPURenderPipelineDescriptorUtil.hpp"
#include "buffer-layout/BufferLayoutData.hpp"
#include "util/wgpu/WebGPUVertexBufferLayoutUtil.hpp"
#include "util/wgpu/WebGPUFragmentStateUtil.hpp"
#include "util/wgpu/WebGPUDepthStencilStateUtil.hpp"

namespace bns
{
    WebGPUPostProcessEffect::WebGPUPostProcessEffect(const Framework &framework)
        : PostProcessEffect(framework)
    {
    }

    WGPUBuffer WebGPUPostProcessEffect::CreateVertexBuffer()
    {
        std::vector<float> data = {
            // position, tex coords
            -1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // top left
            -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bottom left
            1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bottom right

            -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // top left
            1.0f, -1.0f, 0.0f, 1.0f, 1.0f, // bottom right
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f   // top right
        };

        WGPUBuffer vertexBuffer = WebGPUBufferUtil::CreateVertexBuffer(m_device, data, "PostProcessEffectVertexBuffer");
        return vertexBuffer;
    }

    WGPUBindGroupLayout WebGPUPostProcessEffect::CreateTextureBindGroupLayout()
    {
        WGPUBindGroupLayoutEntry bindGroupLayoutEntries[2];

        // Bind group layout for texture
        // Sampler
        bindGroupLayoutEntries[0] = WebGPUBindGroupLayoutEntryUtil::CreateSamplerLayoutEntry(0, WGPUShaderStage_Fragment);
        // Texture
        bindGroupLayoutEntries[1] = WebGPUBindGroupLayoutEntryUtil::CreateTextureLayoutEntry(1, WGPUShaderStage_Fragment);

        // Create layout
        WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc = WebGPUBindGroupLayoutDescriptorUtil::Create(bindGroupLayoutEntries, 2);
        WGPUBindGroupLayout bindGroupLayout = wgpuDeviceCreateBindGroupLayout(m_device, &bindGroupLayoutDesc);

        return bindGroupLayout;
    }

    WGPUBindGroup WebGPUPostProcessEffect::CreateTextureBindGroup()
    {
        if (m_textureBindGroupLayout == nullptr)
        {
            throw std::runtime_error("Texture bind group layout is null.");
        }

        if (m_texture == nullptr)
        {
            throw std::runtime_error("Destination texture is null.");
        }

        WGPUBindGroupEntry bindGroupEntries[2];

        // sampler entry
        WebGPUTexture2D *webGPUTexture2D = static_cast<WebGPUTexture2D*>(m_texture);
        bindGroupEntries[0] = WebGPUBindGroupEntryUtil::Create(0, webGPUTexture2D->Sampler);
        // texture entry
        WGPUTextureView view = webGPUTexture2D->CreateView();
        bindGroupEntries[1] = WebGPUBindGroupEntryUtil::Create(1, view);

        // Create bind group
        WGPUBindGroupDescriptor bindGroupDesc = WebGPUBindGroupDescriptorUtil::Create(m_textureBindGroupLayout, bindGroupEntries, 2);
        WGPUBindGroup bindGroup = wgpuDeviceCreateBindGroup(m_device, &bindGroupDesc);

        return bindGroup;
    }

    WGPURenderPipeline WebGPUPostProcessEffect::CreateRenderPipeline()
    {

        FileLoader fileLoader;
        std::string shaderSource = fileLoader.OpenFile(GetShaderPath());
        WGPUShaderModule shaderModule = WebGPUShaderModuleUtil::Create(m_device, shaderSource);

        WGPUPipelineLayoutDescriptor desc = WebGPUPipelineLayoutDescriptorUtil::Create(&m_textureBindGroupLayout, 1);
        WGPUPipelineLayout layout = wgpuDeviceCreatePipelineLayout(m_device, &desc);

        // 1 layout with 2 attributes
        BufferLayoutDescriptor bufferLayoutDescriptor;
        bufferLayoutDescriptor.Step = StepMode::Vertex;
        bufferLayoutDescriptor.Stride = sizeof(f32) * 5; // x, y, z, u, v
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});

        std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
        vertexBufferLayouts.push_back(bufferLayoutDescriptor);

        WGPUVertexBufferLayout *vertexBuffersLayout = WebGPUVertexBufferLayoutUtil::Create(vertexBufferLayouts);

        // TODO: move to util
        WGPUVertexState vertexState;
        vertexState.nextInChain = nullptr;
        vertexState.entryPoint = "vs_main";
        vertexState.module = shaderModule;
        vertexState.bufferCount = 1;
        vertexState.buffers = vertexBuffersLayout;
        vertexState.constantCount = 0;

        // Fragment state
        // TODO: move to util
        WGPUBlendState blend = {};
        blend.color.operation = WGPUBlendOperation_Add;
        blend.color.srcFactor = WGPUBlendFactor_One;
        blend.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
        blend.alpha.operation = WGPUBlendOperation_Add;
        blend.alpha.srcFactor = WGPUBlendFactor_One;
        blend.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;

        // default color target state
        // TODO: move to util
        WGPUColorTargetState colorTarget = {};
        colorTarget.nextInChain = nullptr;
        colorTarget.format = WGPUTextureFormat_BGRA8Unorm;
        colorTarget.blend = &blend;
        colorTarget.writeMask = WGPUColorWriteMask_All;
        WGPUFragmentState fragmentState = WebGPUFragmentStateUtil::Create(shaderModule, colorTarget, "fs_main");

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

    void WebGPUPostProcessEffect::Initialize()
    {
        m_device = m_framework.Context.WebGPUDevice;

        Vec2u bufferSize = m_framework.GetRenderer().GetBufferSize();
        Texture2D* texture = m_framework.GetTextureFactory()
            .CreateEmpty(bufferSize.X, bufferSize.Y,
                        TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT,
                        TextureFormat::BGRA_8_Unorm);
        m_texture = static_cast<WebGPUTexture2D *>(texture);

        m_vertexBuffer = CreateVertexBuffer();
        m_textureBindGroupLayout = CreateTextureBindGroupLayout();
        m_textureBindGroup = CreateTextureBindGroup();

        m_pipeline = CreateRenderPipeline();
    }

    void WebGPUPostProcessEffect::Draw(void* textureView)
    {
        WGPUDevice device = m_framework.Context.WebGPUDevice;

        // Create a command encoder which can be used to submit GPU operations.
        WGPUCommandEncoderDescriptor desc;
        desc.nextInChain = nullptr;
        desc.label = "PostProcessEffect";
        WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, &desc);

        // Create a render pass for the encoder.
        WGPUTextureView wgpuTextureView = static_cast<WGPUTextureView>(textureView);
        
        WGPURenderPassColorAttachment colorAttachment = WebGPURenderPassColorAttachmentUtil::Create(wgpuTextureView);
        WGPURenderPassDescriptor renderPassDesc = WebGPURenderPassDescriptorUtil::Create(colorAttachment);
        WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDesc);

        // Set the pipeline that will be used for this render pass.
        wgpuRenderPassEncoderSetPipeline(renderPass, m_pipeline);
        wgpuRenderPassEncoderSetBindGroup(renderPass, 0, m_textureBindGroup, 0, nullptr);
        size_t byteSize = sizeof(float) * 5 * 6; // 5 per vertex, 6 vertices
        wgpuRenderPassEncoderSetVertexBuffer(renderPass, 0, m_vertexBuffer, 0, byteSize);
        wgpuRenderPassEncoderDraw(renderPass, 6, 1, 0, 0);
        wgpuRenderPassEncoderEnd(renderPass);

        WGPUCommandBufferDescriptor commandBufferDesc;
        commandBufferDesc.label = "PostProcessEffect";
        WGPUCommandBuffer commandBuffer = wgpuCommandEncoderFinish(encoder, &commandBufferDesc);

        wgpuQueueSubmit(m_framework.Context.WebGPUQueue, 1, &commandBuffer);
    }
}
