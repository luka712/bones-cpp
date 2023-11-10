#include "effects/wgpu/WebGPUTextureCombineEffect.hpp"
#include "WebGPUUtil.hpp"
#include "Framework.hpp"

namespace bns
{
    WebGPUTextureCombineEffectImpl::WebGPUTextureCombineEffectImpl(const Framework &framework)
        : WebGPUEffectImpl(framework)
    {
        m_combineTexture = nullptr;
        m_combineTextureBindGroup = nullptr;
        m_mixValue = 0.5f;
    }

    std::vector<WGPUBindGroupLayout> WebGPUTextureCombineEffectImpl::CreateBindGroupLayouts()
    {
        std::vector<WGPUBindGroupLayout> result = WebGPUEffectImpl::CreateBindGroupLayouts();

        // Combine texture layout
        // create the bind group layout entries
        WGPUBindGroupLayoutEntry combineTextureBindGroupLayoutEntries[2];

        // Bind group layout for texture
        // Sampler
        combineTextureBindGroupLayoutEntries[0] = WebGPUUtil::BindGroupLayoutEntry.CreateSamplerLayoutEntry(0, WGPUShaderStage_Fragment);
        // Texture
        combineTextureBindGroupLayoutEntries[1] = WebGPUUtil::BindGroupLayoutEntry.CreateTextureLayoutEntry(1, WGPUShaderStage_Fragment);

        // Create layout
        WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc = WebGPUUtil::BindGroupLayoutDescriptor.Create(combineTextureBindGroupLayoutEntries, 2);
        WGPUBindGroupLayout bindGroupLayout = wgpuDeviceCreateBindGroupLayout(m_device, &bindGroupLayoutDesc);

        // pust bind group layout to result
        result.push_back(bindGroupLayout);

        // assing to member variable
        m_combineTextureBindGroupLayout = bindGroupLayout;

        // Mix value layout
        // create the bind group layout entries
        WGPUBindGroupLayoutEntry mixValueBindGroupLayoutEntries[1];

        // Bind group layout for mix value
        // Uniform
        mixValueBindGroupLayoutEntries[0] = WebGPUUtil::BindGroupLayoutEntry.CreateUniformBufferLayoutEntry(0, WGPUShaderStage_Fragment);

        // Create layout
        bindGroupLayoutDesc = WebGPUUtil::BindGroupLayoutDescriptor.Create(mixValueBindGroupLayoutEntries, 1);
        bindGroupLayout = wgpuDeviceCreateBindGroupLayout(m_device, &bindGroupLayoutDesc);

        // pust bind group layout to result
        result.push_back(bindGroupLayout);

        // assing to member variable
        m_mixValueBindGroupLayout = bindGroupLayout;

        return result;
    }

    WGPUBindGroup WebGPUTextureCombineEffectImpl::CreateCombineTextureBindGroup()
    {
        // there is no texture, it cannot be created
        if (m_combineTexture == nullptr)
        {
            return nullptr;
        }

        // if there is already a bind group, release it as it is changed
        if (m_combineTextureBindGroup != nullptr)
        {
            wgpuBindGroupRelease(m_combineTextureBindGroup);
        }

        WGPUBindGroupEntry bindGroupEntries[2];

        // sampler entry
        WebGPUTexture2D *webGPUTexture2D = static_cast<WebGPUTexture2D *>(m_combineTexture);
        bindGroupEntries[0] = WebGPUUtil::BindGroupEntry.Create(0, webGPUTexture2D->Sampler);

        // texture entry
        WGPUTextureView view = webGPUTexture2D->CreateView();
        bindGroupEntries[1] = WebGPUUtil::BindGroupEntry.Create(1, view);

        // Create bind group
        WGPUBindGroupDescriptor bindGroupDesc = WebGPUUtil::BindGroupDescriptor.Create(m_combineTextureBindGroupLayout, bindGroupEntries, 2);
        WGPUBindGroup bindGroup = wgpuDeviceCreateBindGroup(m_device, &bindGroupDesc);

        m_combineTextureBindGroup = bindGroup;

        return bindGroup;
    }

    void WebGPUTextureCombineEffectImpl::SetCombineTexture(WebGPUTexture2D *combineTexture)
    {
        m_combineTexture = combineTexture;
        // m_combineTextureBindGroup is assigned by default in CreateBindGroupLayouts.
        CreateCombineTextureBindGroup();
    }

    std::vector<WGPUBindGroup> WebGPUTextureCombineEffectImpl::CreateBindGroups(std::vector<WGPUBindGroupLayout> bindGroupLayouts)
    {
        std::vector<WGPUBindGroup> result = WebGPUEffectImpl::CreateBindGroups(bindGroupLayouts);

        // m_combineTextureBindGroup is assigned by default in CreateBindGroupLayouts.
        WGPUBindGroup combineTextureBindGroup = CreateCombineTextureBindGroup();
        if (combineTextureBindGroup != nullptr)
        {
            result.push_back(combineTextureBindGroup);
        }

        // mix value bind group
        WGPUBindGroupEntry bindGroupEntries[1];

        // uniform entry
        m_mixValueBuffer = WebGPUUtil::Buffer.CreateUniformBuffer(m_device, sizeof(float), "combine_texture_mix_value_buffer");
        bindGroupEntries[0] = WebGPUUtil::BindGroupEntry.Create(0, m_mixValueBuffer, sizeof(float));

        // create bind group
        WGPUBindGroupDescriptor bindGroupDesc = WebGPUUtil::BindGroupDescriptor.Create(m_mixValueBindGroupLayout, bindGroupEntries, 1);
        WGPUBindGroup bindGroup = wgpuDeviceCreateBindGroup(m_device, &bindGroupDesc);

        result.push_back(bindGroup);

        m_mixValueBindGroup = bindGroup;

        return result;
    }

    void WebGPUTextureCombineEffectImpl::Draw(void *texture)
    {
        WGPUDevice device = m_renderer->GetDevice();
        WGPUQueue queue = m_renderer->GetQueue();

        // Create a command encoder which can be used to submit GPU operations.
        WGPUCommandEncoderDescriptor desc;
        desc.nextInChain = nullptr;
        desc.label = "Effect";
        WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, &desc);

        // Create a render pass for the encoder.
        WGPUTexture wgpuTexture = static_cast<WGPUTexture>(texture);
        WGPUTextureView wgpuTextureView = wgpuTextureCreateView(wgpuTexture, nullptr);

        WGPURenderPassColorAttachment colorAttachment = WebGPUUtil::RenderPassColorAttachment.Create(wgpuTextureView);
        WGPURenderPassDescriptor renderPassDesc = WebGPUUtil::RenderPassDescriptor.Create(colorAttachment);
        WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDesc);

        // TODO: this can be written when value is set! (not every frame)
        // write mix value to buffer
        wgpuQueueWriteBuffer(queue, m_mixValueBuffer, 0, &m_mixValue, sizeof(float));

        // Set the pipeline that will be used for this render pass.
        wgpuRenderPassEncoderSetPipeline(renderPass, m_pipeline);

        // Set bind groups
        wgpuRenderPassEncoderSetBindGroup(renderPass, 0, m_sourceTextureBindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetBindGroup(renderPass, 1, m_combineTextureBindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetBindGroup(renderPass, 2, m_mixValueBindGroup, 0, nullptr);

        // Set buffers
        size_t byteSize = sizeof(float) * 5 * 6; // 5 per vertex, 6 vertices
        wgpuRenderPassEncoderSetVertexBuffer(renderPass, 0, m_vertexBuffer, 0, byteSize);

        wgpuRenderPassEncoderDraw(renderPass, 6, 1, 0, 0);
        wgpuRenderPassEncoderEnd(renderPass);

        WGPUCommandBufferDescriptor commandBufferDesc;
        commandBufferDesc.label = "combine_texture_post_process_effect";
        WGPUCommandBuffer commandBuffer = wgpuCommandEncoderFinish(encoder, &commandBufferDesc);

        wgpuQueueSubmit(queue, 1, &commandBuffer);

        // release created resources
        wgpuTextureViewRelease(wgpuTextureView);
        wgpuCommandEncoderRelease(encoder);
    }

} // namespace bns