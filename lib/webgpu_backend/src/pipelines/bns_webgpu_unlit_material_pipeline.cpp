#if USE_WEBGPU

#include "pipelines/bns_webgpu_unlit_render_pipeline.hpp"
#include "renderer/bns_webgpu_renderer.hpp"
#include "loaders/bns_file_loader.hpp"
#include "bns_webgpu_util.hpp"

namespace bns
{
    WebGPUUnlitRenderPipeline::WebGPUUnlitRenderPipeline(Renderer *renderer, UniformBuffer<Mat4x4f> *cameraBuffer, InstanceBuffer<Mat4x4f> *modelBuffer)
    {
        m_device = static_cast<WebGPURenderer *>(renderer)->GetDevice();
        m_renderer = static_cast<WebGPURenderer *>(renderer);
        m_cameraBuffer = static_cast<WebGPUUniformBuffer<Mat4x4f> *>(cameraBuffer);
        m_modelBuffer = static_cast<WebGPUInstanceBuffer<Mat4x4f> *>(modelBuffer);
    }

    void WebGPUUnlitRenderPipeline::SetDiffuseColor(Color diffuseColor)
    {
        m_diffuseColor = diffuseColor;
        m_diffuseColorBuffer->Update(diffuseColor);
    }

    void WebGPUUnlitRenderPipeline::SetTextureTilling(Vec2f textureTilling)
    {
        m_textureTilling = textureTilling;
        m_textureTillingBuffer->Update(textureTilling);
    }

    void WebGPUUnlitRenderPipeline::SetDiffuseTexture(Texture2D *diffuseTexture)
    {
        m_diffuseTexture = diffuseTexture;
        CreateDiffuseTextureBindGroup();
    }

    void WebGPUUnlitRenderPipeline::CreateShaderModule()
    {
        // Get shader module.
        FileLoader fileLoader;
        std::string shaderCode = fileLoader.LoadFile("shaders/webgpu/material/unlit_material.wgsl", {
           { "##INSTANCE_COUNT##", std::to_string(m_modelBuffer->GetInstanceCount()) }
        });
        m_shaderModule = WebGPUUtil::ShaderModule.Create(m_device, shaderCode, "unlit_material");

        LOG("WebGPUUnlitMaterialPipeline: Shader module created.");
    }

    void WebGPUUnlitRenderPipeline::CreateBindGroupLayouts()
    {
        // Transforms and texture tilling.
        std::vector<WebGPUBindGroupLayoutEntry> webGPUBindGroupLayoutEntry = {
            WebGPUBindGroupLayoutEntry::CreateUniformBufferLayoutEntry(0, ShaderType::Vertex), // Transforms
            WebGPUBindGroupLayoutEntry::CreateUniformBufferLayoutEntry(1, ShaderType::Vertex), // Texture tilling
        };
        m_modelBindGroupLayout = WebGPUUtil::BindGroupLayout.Create(m_device, webGPUBindGroupLayoutEntry);

        // Projection view matrix.
        webGPUBindGroupLayoutEntry = {
            WebGPUBindGroupLayoutEntry::CreateUniformBufferLayoutEntry(0, ShaderType::Vertex), // Projection view matrix
        };
        m_cameraBindGroupLayout = WebGPUUtil::BindGroupLayout.Create(m_device, webGPUBindGroupLayoutEntry);

        // Texture and sampler.
        webGPUBindGroupLayoutEntry = {
            WebGPUBindGroupLayoutEntry::CreateTextureLayoutEntry(0, ShaderType::Fragment), // Texture
            WebGPUBindGroupLayoutEntry::CreateSamplerLayoutEntry(1, ShaderType::Fragment), // Sampler
        };
        m_textureBindGroupLayout = WebGPUUtil::BindGroupLayout.Create(m_device, webGPUBindGroupLayoutEntry);

        // Diffuse color.
        webGPUBindGroupLayoutEntry = {
            WebGPUBindGroupLayoutEntry::CreateUniformBufferLayoutEntry(0, ShaderType::Fragment), // Diffuse color
        };
        m_materialBindGroupLayout = WebGPUUtil::BindGroupLayout.Create(m_device, webGPUBindGroupLayoutEntry);

        LOG("WebGPUUnlitMaterialPipeline: Bind group layouts created.");
    }

    void WebGPUUnlitRenderPipeline::CreatePipelineLayout()
    {
        std::vector<WGPUBindGroupLayout> bindGroupLayouts = {
            m_modelBindGroupLayout,
            m_cameraBindGroupLayout,
            m_textureBindGroupLayout,
            m_materialBindGroupLayout};

        m_pipelineLayout = WebGPUPipelineLayoutUtil::Create(m_device, bindGroupLayouts);

        LOG("WebGPUUnlitMaterialPipeline: Pipeline layout created.");
    }

    void WebGPUUnlitRenderPipeline::CreateResources()
    {
        m_textureTillingBuffer = new WebGPUUniformBuffer<Vec2f>(m_renderer);
        m_textureTillingBuffer->Initialize();

        m_diffuseColorBuffer = new WebGPUUniformBuffer<Color>(m_renderer);
        m_diffuseColorBuffer->Initialize();

        m_diffuseTexture = WebGPUTexture2D::CreateEmpty(m_renderer, 64, 64);
        m_diffuseTexture->Initialize();

        // This will write to buffers
        SetTextureTilling(Vec2f::One());
        SetDiffuseColor(Color::White())

        LOG("WebGPUUnlitMaterialPipeline: Resources created created.");
    }

    void WebGPUUnlitRenderPipeline::CreatePipeline()
    {
        std::vector<BufferLayoutDescriptor> bufferLayoutDescriptors(1);
        bufferLayoutDescriptors[0].StepMode = VertexStepMode::Vertex;
        bufferLayoutDescriptors[0].Stride = (3 + 4 + 2) * sizeof(f32);
        bufferLayoutDescriptors[0].Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptors[0].Attributes.push_back({VertexFormat::Float32x4, 1, sizeof(f32) * 3});
        bufferLayoutDescriptors[0].Attributes.push_back({VertexFormat::Float32x2, 2, sizeof(f32) * (3 + 4)});

        m_pipeline = WebGPUUtil::RenderPipeline.Create(m_device, m_shaderModule, m_pipelineLayout, bufferLayoutDescriptors);

        LOG("WebGPUUnlitMaterialPipeline: Pipeline created.");
    }

    void WebGPUUnlitRenderPipeline::CreateBindGroups()
    {
        CreateDiffuseTextureBindGroup();

        // Create model bind group.
        std::vector<WebGPUBindGroupEntry> bindGroupEntries(2);
        bindGroupEntries[0].Binding = 0;
        bindGroupEntries[0].Buffer = m_modelBuffer->GetBuffer();
        bindGroupEntries[0].Offset = 0;
        bindGroupEntries[0].Size = sizeof(Mat4x4f) * m_modelBuffer->GetInstanceCount();
        bindGroupEntries[1].Binding = 1;
        bindGroupEntries[1].Buffer = m_textureTillingBuffer->GetBuffer();
        bindGroupEntries[1].Offset = 0;
        bindGroupEntries[1].Size = sizeof(Vec2f);
        m_modelBindGroup = WebGPUUtil::BindGroup.Create(m_device, m_modelBindGroupLayout, bindGroupEntries, "Unlit Render Pipeline Model Bind Group");

        // Create camera bind group.
        bindGroupEntries.resize(1);
        bindGroupEntries[0].Binding = 0;
        bindGroupEntries[0].Buffer = m_cameraBuffer->GetBuffer();
        bindGroupEntries[0].Offset = 0;
        bindGroupEntries[0].Size = sizeof(Mat4x4f);
        m_cameraBindGroup = WebGPUUtil::BindGroup.Create(m_device, m_cameraBindGroupLayout, bindGroupEntries, "Unlit Render Pipeline Camera Bind Group");

        // Create material bind group.
        bindGroupEntries[0].Binding = 0;
        bindGroupEntries[0].Buffer = m_diffuseColorBuffer->GetBuffer();
        bindGroupEntries[0].Offset = 0;
        bindGroupEntries[0].Size = sizeof(Color);
        m_materialBindGroup = WebGPUUtil::BindGroup.Create(m_device, m_materialBindGroupLayout, bindGroupEntries, "Unlit Render Pipeline Material Bind Group");
    }

    void WebGPUUnlitRenderPipeline::CreateDiffuseTextureBindGroup()
    {
        WebGPUTexture2D* wgpuTexture = static_cast<WebGPUTexture2D*>(m_diffuseTexture);

        std::vector<WebGPUBindGroupEntry> bindGroupEntries(2);
        bindGroupEntries[0].Binding = 0;
        bindGroupEntries[0].TextureView = wgpuTexture->CreateView("Unlit Render Pipeline Diffuse Texture");
        bindGroupEntries[1].Binding = 1;
        bindGroupEntries[1].Sampler = wgpuTexture->Sampler;

        m_textureBindGroup = WebGPUUtil::BindGroup.Create(m_device, m_textureBindGroupLayout, bindGroupEntries, "Unlit Render Pipeline Diffuse Texture Bind Group");
    }

    void WebGPUUnlitRenderPipeline::Initialize()
    {
        CreateShaderModule();
        CreateBindGroupLayouts();
        CreateResources();
        CreatePipelineLayout();
        CreatePipeline();
        CreateBindGroups();

        // Dispose
        WebGPUUtil::ShaderModule.Dispose(m_shaderModule);
        WebGPUUtil::PipelineLayout.Dispose(m_pipelineLayout);
    }

    void WebGPUUnlitRenderPipeline::Render(VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer, u32 instanceCount)
    {
        CreateDiffuseTextureBindGroup();

        WebGPUVertexBuffer& wgpuVertexBuffer = *static_cast<WebGPUVertexBuffer*>(vertexBuffer);
        WebGPUIndexBuffer& wgpuIndexBuffer = *static_cast<WebGPUIndexBuffer*>(indexBuffer);
        
        WGPURenderPassEncoder pass = m_renderer->GetCurrentRenderPassEncoder();

        wgpuRenderPassEncoderSetPipeline(pass, m_pipeline);

        // Set attributes
        wgpuRenderPassEncoderSetVertexBuffer(pass, 0, wgpuVertexBuffer.GetBuffer(), 0, wgpuVertexBuffer.GetByteSize());
        wgpuRenderPassEncoderSetIndexBuffer(pass, wgpuIndexBuffer.GetBuffer(), WGPUIndexFormat_Uint16, 0, wgpuIndexBuffer.GetByteSize());

        // Set bind groups
        wgpuRenderPassEncoderSetBindGroup(pass, 0, m_modelBindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetBindGroup(pass, 1, m_cameraBindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetBindGroup(pass, 2, m_textureBindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetBindGroup(pass, 3, m_materialBindGroup, 0, nullptr);

        wgpuRenderPassEncoderDrawIndexed(pass, wgpuIndexBuffer.GetIndicesCount(), instanceCount, 0, 0, 0);
    }

    void WebGPUUnlitRenderPipeline::Dispose()
    {
        m_textureTillingBuffer->Dispose();
        delete m_textureTillingBuffer;
        m_textureTillingBuffer = nullptr;

        m_diffuseColorBuffer->Dispose();
        delete m_diffuseColorBuffer;
        m_diffuseColorBuffer = nullptr;

        WebGPUUtil::BindGroupLayout.Dispose(m_modelBindGroupLayout);
        WebGPUUtil::BindGroupLayout.Dispose(m_cameraBindGroupLayout);
        WebGPUUtil::BindGroupLayout.Dispose(m_textureBindGroupLayout);
        WebGPUUtil::BindGroupLayout.Dispose(m_materialBindGroupLayout);
    }
}

#endif
