#if USE_WEBGPU

#include "pipelines/bns_webgpu_unlit_material_pipeline.hpp"
#include "renderer/bns_webgpu_renderer.hpp"
#include "loaders/bns_file_loader.hpp"
#include "bns_webgpu_util.hpp"

namespace bns
{
    WebGPUUnlitMaterialPipeline::WebGPUUnlitMaterialPipeline(Renderer *renderer, ConstantBuffer<Mat4x4f> *cameraBuffer, ConstantBuffer<Mat4x4f> *modelBuffer)
    {
        m_device = static_cast<WebGPURenderer *>(renderer)->GetDevice();
        m_renderer = static_cast<WebGPURenderer *>(renderer);
        m_cameraBuffer = static_cast<WebGPUConstantBuffer<Mat4x4f> *>(cameraBuffer);
        m_modelBuffer = static_cast<WebGPUConstantBuffer<Mat4x4f> *>(modelBuffer);
    }

    void WebGPUUnlitMaterialPipeline::CreateShaderModule()
    {
        // Get shader module.
        FileLoader fileLoader;
        std::string shaderCode = fileLoader.LoadFile("shaders/webgpu/material/unlit_material.wgsl");
        m_shaderModule = WebGPUUtil::ShaderModule.Create(m_device, shaderCode, "unlit_material");

        LOG("WebGPUUnlitMaterialPipeline: Shader module created.");
    }

    void WebGPUUnlitMaterialPipeline::CreateBindGroupLayouts()
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

    void WebGPUUnlitMaterialPipeline::CreatePipelineLayout()
    {
        std::vector<WGPUBindGroupLayout> bindGroupLayouts = {
            m_modelBindGroupLayout,
            m_cameraBindGroupLayout,
            m_textureBindGroupLayout,
            m_materialBindGroupLayout};

        m_pipelineLayout = WebGPUPipelineLayoutUtil::Create(m_device, bindGroupLayouts);

        LOG("WebGPUUnlitMaterialPipeline: Pipeline layout created.");
    }

    void WebGPUUnlitMaterialPipeline::CreateBuffers()
    {
        m_textureTillingBuffer = new WebGPUConstantBuffer<Mat4x4f>(m_renderer);
        m_textureTillingBuffer->Initialize();

        m_diffuseColorBuffer = new WebGPUConstantBuffer<Mat4x4f>(m_renderer);
        m_diffuseColorBuffer->Initialize();

        LOG("WebGPUUnlitMaterialPipeline: Buffers created.");
    }

    void WebGPUUnlitMaterialPipeline::CreatePipeline()
    {
        std::vector<BufferLayoutDescriptor> bufferLayoutDescriptors(1);
        bufferLayoutDescriptors[0].Step = VertexStepMode::Vertex;
        bufferLayoutDescriptors[0].Stride = (3 + 4 + 2) * sizeof(f32);
        bufferLayoutDescriptors[0].Attributes.push_back({VertexFormat::Float32x3, 0, 0});
        bufferLayoutDescriptors[0].Attributes.push_back({VertexFormat::Float32x4, 1, sizeof(f32) * 3});
        bufferLayoutDescriptors[0].Attributes.push_back({VertexFormat::Float32x2, 2, sizeof(f32) * (3 + 4)});

        m_pipeline = WebGPUUtil::RenderPipeline.Create(m_device, m_shaderModule, m_pipelineLayout, bufferLayoutDescriptors);

        LOG("WebGPUUnlitMaterialPipeline: Pipeline created.");
    }

    void WebGPUUnlitMaterialPipeline::Initialize()
    {
        CreateShaderModule();
        CreateBindGroupLayouts();
        CreateBuffers();
        CreatePipelineLayout();
        CreatePipeline();

        // Dispose
        WebGPUUtil::ShaderModule.Dispose(m_shaderModule);
        WebGPUUtil::PipelineLayout.Dispose(m_pipelineLayout);
    }

    void WebGPUUnlitMaterialPipeline::Dispose()
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