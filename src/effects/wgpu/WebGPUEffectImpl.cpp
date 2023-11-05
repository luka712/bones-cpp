#include "effects/wgpu/WebGPUEffectImpl.hpp"
#include "Framework.hpp"
#include "util/WebGPUUtil.hpp"
#include "util/wgpu/WebGPUBufferUtil.hpp"
#include "util/wgpu/WebGPUBindGroupLayoutEntryUtil.hpp"
#include "util/wgpu/WebGPUBindGroupLayoutDescriptorUtil.hpp"
#include "util/wgpu/WebGPUPipelineLayoutDescriptorUtil.hpp"
#include "util/wgpu/WebGPURenderPipelineDescriptorUtil.hpp"
#include "buffer-layout/BufferLayoutData.hpp"
#include "util/wgpu/WebGPUDepthStencilStateUtil.hpp"

namespace bns
{
    WebGPUEffectImpl::WebGPUEffectImpl(const Framework &framework)
        : Effect(framework)
    {
    }

    WebGPUEffectImpl::~WebGPUEffectImpl()
    {
        m_sourceTexture->Release();
        wgpuBufferRelease(m_vertexBuffer);
        wgpuBindGroupLayoutRelease(m_sourceTextureBindGroupLayout);
        wgpuBindGroupRelease(m_sourceTextureBindGroup);
        wgpuRenderPipelineRelease(m_pipeline);
    }

    void WebGPUEffectImpl::SetSourceTexture(Texture2D *sourceTexture)
    {
        m_sourceTexture = sourceTexture;
        WebGPUTexture2D *tex = static_cast<WebGPUTexture2D *>(sourceTexture);
        m_sourceTextureBindGroup = CreateTextureBindGroup(*tex);
    }

    WGPUBuffer WebGPUEffectImpl::CreateVertexBuffer()
    {
        std::vector<float> data = {
            // position, tex coords
            -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
            -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bottom left
            1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bottom right

            -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // top left
            1.0f, -1.0f, 0.0f, 1.0f, 1.0f, // bottom right
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f   // top right
        };

        WGPUBuffer vertexBuffer = WebGPUUtilDeprecated::Buffer.CreateVertexBuffer(m_device, data, "Effect Vertex Buffer");
        return vertexBuffer;
    }

    std::vector<WGPUBindGroupLayout> WebGPUEffectImpl::CreateBindGroupLayouts()
    {
        // result
        std::vector<WGPUBindGroupLayout> result;

        // create the bind group layout entries
        WGPUBindGroupLayoutEntry bindGroupLayoutEntries[2];

        // Bind group layout for texture
        // Sampler
        bindGroupLayoutEntries[0] = WebGPUBindGroupLayoutEntryUtil::CreateSamplerLayoutEntry(0, WGPUShaderStage_Fragment);
        // Texture
        bindGroupLayoutEntries[1] = WebGPUBindGroupLayoutEntryUtil::CreateTextureLayoutEntry(1, WGPUShaderStage_Fragment);

        // Create layout
        WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc = WebGPUBindGroupLayoutDescriptorUtil::Create(bindGroupLayoutEntries, 2);
        WGPUBindGroupLayout bindGroupLayout = wgpuDeviceCreateBindGroupLayout(m_device, &bindGroupLayoutDesc);

        // pust bind group layout to result
        result.push_back(bindGroupLayout);

        // assing to member variable
        m_sourceTextureBindGroupLayout = bindGroupLayout;

        return result;
    }

    WGPUBindGroup WebGPUEffectImpl::CreateTextureBindGroup(WebGPUTexture2D &texture)
    {
        WGPUBindGroupEntry bindGroupEntries[2];

        // sampler entry
        bindGroupEntries[0] = WebGPUUtilDeprecated::BindGroupEntry.Create(0, texture.Sampler);
        // texture entry
        WGPUTextureView view = texture.CreateView();
        bindGroupEntries[1] = WebGPUUtilDeprecated::BindGroupEntry.Create(1, view);

        // Create bind group
        WGPUBindGroupDescriptor bindGroupDesc = WebGPUUtilDeprecated::BindGroupDescriptor.Create(m_sourceTextureBindGroupLayout, bindGroupEntries, 2);
        WGPUBindGroup bindGroup = wgpuDeviceCreateBindGroup(m_device, &bindGroupDesc);

        return bindGroup;
    }

    std::vector<WGPUBindGroup> WebGPUEffectImpl::CreateBindGroups(std::vector<WGPUBindGroupLayout> layouts)
    {
        std::vector<WGPUBindGroup> result;

        if (m_sourceTextureBindGroupLayout == nullptr)
        {
            throw std::runtime_error("Texture bind group layout is null.");
        }

        if (m_sourceTexture == nullptr)
        {
            throw std::runtime_error("Source texture is null.");
        }

        WGPUBindGroup bindGroup = CreateTextureBindGroup(*static_cast<WebGPUTexture2D *>(m_sourceTexture));

        // push bind group to result
        result.push_back(bindGroup);

        // assign to member variable
        m_sourceTextureBindGroup = bindGroup;

        return result;
    }

    WGPURenderPipeline WebGPUEffectImpl::CreateRenderPipeline(std::vector<WGPUBindGroupLayout> layouts)
    {

        FileLoader fileLoader;
        std::string shaderSource = fileLoader.LoadFile(GetShaderPath());
        WGPUShaderModule shaderModule = WebGPUUtilDeprecated::ShaderModule.Create(m_device, shaderSource);

        // Create pipeline layout. Here the global bind group layout is assigned.
        WGPUPipelineLayoutDescriptor desc = WebGPUPipelineLayoutDescriptorUtil::Create(layouts.data(), layouts.size());
        WGPUPipelineLayout layout = wgpuDeviceCreatePipelineLayout(m_device, &desc);

        // 1 layout with 2 attributes
        BufferLayoutDescriptor bufferLayoutDescriptor;
        bufferLayoutDescriptor.Step = StepMode::Vertex;
        bufferLayoutDescriptor.Stride = sizeof(f32) * 5; // x, y, z, u, v
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptor.Attributes.push_back({VertexFormat::Float32x2, 1, sizeof(f32) * 3});

        std::vector<BufferLayoutDescriptor> vertexBufferLayouts;
        vertexBufferLayouts.push_back(bufferLayoutDescriptor);

        WGPUVertexBufferLayout *vertexBuffersLayout = WebGPUUtilDeprecated::VertexBufferLayout.Create(vertexBufferLayouts);

        // TODO: move to util
        WGPUVertexState vertexState;
        vertexState.nextInChain = nullptr;
        vertexState.entryPoint = "vs_main";
        vertexState.module = shaderModule;
        vertexState.bufferCount = 1;
        vertexState.buffers = vertexBuffersLayout;
        vertexState.constantCount = 0;

        // Fragment state
        WGPUBlendState blend = WebGPUUtilDeprecated::BlendState.Create();

        // default color target state
        // TODO: move to util
        WGPUColorTargetState colorTarget = {};
        colorTarget.nextInChain = nullptr;
        colorTarget.format = WGPUTextureFormat_BGRA8Unorm;
        colorTarget.blend = &blend;
        colorTarget.writeMask = WGPUColorWriteMask_All;
        std::string fragFn = "fs_main";
        WGPUFragmentState fragmentState = WebGPUUtilDeprecated::FragmentState.Create(shaderModule, colorTarget, fragFn);

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

    void WebGPUEffectImpl::Initialize()
    {
        m_device = m_framework.Context.WebGPUDevice;

        Vec2u bufferSize = m_framework.GetRenderer()->GetBufferSize();
        Texture2D *texture = m_framework.GetTextureManager()
                                 .CreateEmpty(bufferSize.X, bufferSize.Y,
                                              TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT,
                                              TextureFormat::BGRA_8_Unorm);
        m_sourceTexture = static_cast<WebGPUTexture2D *>(texture);

        m_vertexBuffer = CreateVertexBuffer();

        std::vector<WGPUBindGroupLayout> layouts = CreateBindGroupLayouts();
        std::vector<WGPUBindGroup> bindGroups = CreateBindGroups(layouts);

        m_pipeline = CreateRenderPipeline(layouts);
    }

    void WebGPUEffectImpl::Draw(void *destinationTexture)
    {
        WGPUDevice device = m_framework.Context.WebGPUDevice;

        // Create a command encoder which can be used to submit GPU operations.
        WGPUCommandEncoderDescriptor desc;
        desc.nextInChain = nullptr;
        desc.label = "Effect";
        WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, &desc);

        // Create a render pass for the encoder.
        WGPUTexture wgpuTexture = static_cast<WGPUTexture>(destinationTexture);
        WGPUTextureView wgpuTextureView = wgpuTextureCreateView(wgpuTexture, nullptr);

        WGPURenderPassColorAttachment colorAttachment = WebGPUUtilDeprecated::RenderPassColorAttachment.Create(wgpuTextureView);
        WGPURenderPassDescriptor renderPassDesc = WebGPUUtilDeprecated::RenderPassDescriptor.Create(colorAttachment);
        WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDesc);

        // Set the pipeline that will be used for this render pass.
        wgpuRenderPassEncoderSetPipeline(renderPass, m_pipeline);
        wgpuRenderPassEncoderSetBindGroup(renderPass, 0, m_sourceTextureBindGroup, 0, nullptr);
        size_t byteSize = sizeof(float) * 5 * 6; // 5 per vertex, 6 vertices
        wgpuRenderPassEncoderSetVertexBuffer(renderPass, 0, m_vertexBuffer, 0, byteSize);
        wgpuRenderPassEncoderDraw(renderPass, 6, 1, 0, 0);
        wgpuRenderPassEncoderEnd(renderPass);

        WGPUCommandBufferDescriptor commandBufferDesc;
        commandBufferDesc.label = "Effect";
        WGPUCommandBuffer commandBuffer = wgpuCommandEncoderFinish(encoder, &commandBufferDesc);

        wgpuQueueSubmit(m_framework.Context.WebGPUQueue, 1, &commandBuffer);

        // release created resources
        wgpuTextureViewRelease(wgpuTextureView);
        wgpuCommandEncoderRelease(encoder);
    }
}