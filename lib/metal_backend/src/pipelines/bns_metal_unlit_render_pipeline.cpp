#if USE_METAL

#include "renderer/bns_metal_renderer.hpp"
#include "pipelines/bns_metal_unlit_render_pipeline.hpp"
#include "bns_metal_util.hpp"
#include "loaders/bns_file_loader.hpp"
#include <functional>
#include "texture/bns_metal_texture2d.hpp"

namespace bns
{
    MetalUnlitRenderPipeline::MetalUnlitRenderPipeline(Renderer *renderer, MetalUniformBuffer<Mat4x4f> *cameraBuffer, MetalUniformBuffer<Mat4x4f> *modelBuffer)
        : m_cameraBuffer(cameraBuffer), m_modelBuffer(modelBuffer)
    {
        m_renderer = static_cast<MetalRenderer *>(renderer);
    }

    void MetalUnlitRenderPipeline::CreateLibrary()
    {
        FileLoader fileLoader;
        std::string shaderCode = fileLoader.LoadFile("shaders/metal/material/unlit_material.metal");
        m_library = MetalUtil::Library.Create(m_renderer->GetDevice(), shaderCode, "Unlit Render Pipeline Library");
    }

    void MetalUnlitRenderPipeline::CreatePipeline()
    {
        m_pipeline = MetalUtil::RenderPipelineState.Create(
            m_renderer->GetDevice(),
            m_library,
            "main_vs",
            "main_fs",
            "Unlit Render Pipeline");
    }

    void MetalUnlitRenderPipeline::CreateResources()
    {
        // Create the resources.
        m_diffuseColorBuffer = new MetalUniformBuffer<Color>(m_renderer, "Diffuse Color Buffer");
        m_diffuseColorBuffer->Initialize();
        m_textureTillingBuffer = new MetalUniformBuffer<Vec2f>(m_renderer, "Texture Tilling Buffer");
        m_textureTillingBuffer->Initialize();

        m_diffuseTexture = MetalTexture2D::CreateEmpty(m_renderer, 1, 1);

        SetDiffuseColor(Color::White());
        SetTextureTilling(Vec2f(1.0f, 1.0f));

        LOG("MetalUnlitRenderPipeline: Resources created.");
    }

    void MetalUnlitRenderPipeline::Initialize()
    {
        CreateLibrary();
        CreatePipeline();
        CreateResources();

        // Release resources.
        m_library->release();
    }

    void MetalUnlitRenderPipeline::SetDiffuseColor(Color color)
    {
        m_diffuseColor = color;
        m_diffuseColorBuffer->Update(color);
    }

    void MetalUnlitRenderPipeline::SetTextureTilling(Vec2f tilling)
    {
        m_textureTilling = tilling;
        m_textureTillingBuffer->Update(tilling);
    }

    void MetalUnlitRenderPipeline::SetDiffuseTexture(Texture2D *texture)
    {
        m_diffuseTexture = texture;
    }

    void MetalUnlitRenderPipeline::Render(MetalVertexBuffer &vertexBuffer, MetalIndexBuffer &indexBuffer, u32 instanceCount)
    {
        MetalTexture2D *metalDiffuseTexture = static_cast<MetalTexture2D *>(m_diffuseTexture);

        MTL::RenderCommandEncoder *renderCommandEncoder = m_renderer->GetRenderCommandEncoder();
        renderCommandEncoder->setRenderPipelineState(m_pipeline);

        // Set the vertex buffer.
        renderCommandEncoder->setVertexBuffer(vertexBuffer.GetBuffer(), 0, 0);

        // Set uniform/constant vertex buffers
        renderCommandEncoder->setVertexBuffer(m_modelBuffer->GetBuffer(), 0, 1);
        renderCommandEncoder->setVertexBuffer(m_textureTillingBuffer->GetBuffer(), 0, 2);
        renderCommandEncoder->setVertexBuffer(m_cameraBuffer->GetBuffer(), 0, 3);

        // Set uniform/constant fragment buffers
        renderCommandEncoder->setFragmentBuffer(m_diffuseColorBuffer->GetBuffer(), 0, 0);

        // Set the diffuse texture.
        renderCommandEncoder->setFragmentTexture(metalDiffuseTexture->Texture, 0);
        renderCommandEncoder->setFragmentSamplerState(metalDiffuseTexture->Sampler, 0);

        // Set the index buffer.
        renderCommandEncoder->drawIndexedPrimitives(MTL::PrimitiveTypeTriangle, indexBuffer.GetIndicesCount(), MTL::IndexTypeUInt16, indexBuffer.GetBuffer(), 0, instanceCount);
    }

    void MetalUnlitRenderPipeline::Dispose()
    {
        m_cameraBuffer->Dispose();
        m_modelBuffer->Dispose();
        m_diffuseColorBuffer->Dispose();
        m_textureTillingBuffer->Dispose();
        m_diffuseTexture->Dispose();
        MetalUtil::RenderPipelineState.Dispose(m_pipeline);
    }

} // namespace bns

#endif
