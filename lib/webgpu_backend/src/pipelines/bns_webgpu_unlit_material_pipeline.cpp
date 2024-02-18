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
    }

    void WebGPUUnlitMaterialPipeline::CreateBuffers()
    {
        m_textureTillingBuffer = new WebGPUConstantBuffer<Mat4x4f>(m_renderer);
        m_textureTillingBuffer->Initialize();

        m_diffuseColorBuffer = new WebGPUConstantBuffer<Mat4x4f>(m_renderer);
        m_diffuseColorBuffer->Initialize();
    }

    void WebGPUUnlitMaterialPipeline::Initialize()
    {
        // Get shader module.
        FileLoader fileLoader;
        std::string shaderCode = fileLoader.LoadFile("shaders/webgpu/material/unlit_material.wgsl");
        WGPUShaderModule shaderModule = WebGPUUtil::ShaderModule.Create(m_device, shaderCode, "unlit_material");

        CreateBindGroupLayouts();
        CreateBuffers();

        // Dispose
        WebGPUUtil::ShaderModule.Dispose(shaderModule);
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