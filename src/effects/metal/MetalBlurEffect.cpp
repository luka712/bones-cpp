#include "effects/metal/MetalBlurEffect.hpp"
#include "util/MetalUtil.hpp"
#include "Framework.hpp"

namespace bns
{
#pragma region Interface

    MetalBlurEffect::MetalBlurEffect(const Framework &framework)
        : BlurEffect(framework)
    {
        m_impl = new MetalBlurEffectImpl(framework);
    }

#pragma endregion

#pragma region Implementation

    MetalBlurEffectImpl::MetalBlurEffectImpl(const Framework &framework)
        : MetalEffectImpl(framework)
    {
    }

    void MetalBlurEffectImpl::Initialize()
    {
        m_device = m_framework.Context.MetalDevice;
        Vec2u bufferSize = m_framework.GetRenderer().GetBufferSize();

        // Textures
        Texture2D *horizontalTexture = m_framework.GetTextureFactory()
                                           .CreateEmpty(bufferSize.X, bufferSize.Y,
                                                        TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT,
                                                        TextureFormat::BGRA_8_Unorm);
        m_sourceTexture = static_cast<MetalTexture2D *>(horizontalTexture);

        Texture2D *verticalTexture = m_framework.GetTextureFactory()
                                         .CreateEmpty(bufferSize.X, bufferSize.Y,
                                                      TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT,
                                                      TextureFormat::BGRA_8_Unorm);
        m_midStepTexture = static_cast<MetalTexture2D *>(verticalTexture);

        // Pipelines
        FileLoader fileLoader;
        std::string shaderSource = fileLoader.LoadFile(GetShaderPath());

        MTL::Library *pLibrary = MetalUtil::Library.Create(m_device, shaderSource);
        m_horizontalPassPipeline = CreateRenderPipeline(pLibrary, "vs_main", "fs_main_horizontal_pass");
        m_verticalPassPipeline = CreateRenderPipeline(pLibrary, "vs_main", "fs_main_vertical_pass");
        pLibrary->release();

        // Buffers
        m_vertexBuffer = CreateVertexBuffer();
    }

    void MetalBlurEffectImpl::Draw(void *destinationTexture)
    {
        MTL::Device *device = m_framework.Context.MetalDevice;
        MTL::CommandQueue *queue = m_framework.Context.MetalCommandQueue;

        // 

        // Convert to Metal types
        MTL::Texture *mtlDestTexture = static_cast<MTL::Texture *>(destinationTexture);

        // HORIZONTAL PASS
        MTL::CommandBuffer *horizontaPassCommandBuffer = queue->commandBuffer();

        // Create a command horizontalPassEncoder which can be used to submit GPU operations.
        MTL::RenderPassDescriptor *horizontalPassDesc = MTL::RenderPassDescriptor::renderPassDescriptor();

        MTL::RenderPassColorAttachmentDescriptor *horizontalPassColorAttachment = horizontalPassDesc->colorAttachments()->object(0);
        horizontalPassColorAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
        horizontalPassColorAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
        horizontalPassColorAttachment->setTexture(m_midStepTexture->Texture); // horizontal pass writes to vertical pass texture

        MTL::RenderCommandEncoder *horizontalPassEncoder = horizontaPassCommandBuffer->renderCommandEncoder(horizontalPassDesc);

        // Set the pipeline that will be used for this render pass.
        horizontalPassEncoder->setRenderPipelineState(m_horizontalPassPipeline);
        horizontalPassEncoder->setVertexBuffer(m_vertexBuffer, 0, 0);

        // Set texture
        MetalTexture2D *mtlSourceTex = static_cast<MetalTexture2D *>(m_sourceTexture);
        horizontalPassEncoder->setFragmentTexture(mtlSourceTex->Texture, 0);
        horizontalPassEncoder->setFragmentSamplerState(mtlSourceTex->Sampler, 0);

        horizontalPassEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 0, 6, 1);

        horizontalPassEncoder->endEncoding();
        horizontaPassCommandBuffer->commit();

        // VERTICAL PASS
        MTL::CommandBuffer *verticalPassCommandBuffer = queue->commandBuffer();

        // Create a command horizontalPassEncoder which can be used to submit GPU operations.
        MTL::RenderPassDescriptor *verticalPassDesc = MTL::RenderPassDescriptor::renderPassDescriptor();

        MTL::RenderPassColorAttachmentDescriptor *verticalPassColorAttachment = verticalPassDesc->colorAttachments()->object(0);
        verticalPassColorAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
        verticalPassColorAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
        verticalPassColorAttachment->setTexture(mtlDestTexture); // write into destination texture, usually this is scene texture

        MTL::RenderCommandEncoder *verticalPassEncoder = verticalPassCommandBuffer->renderCommandEncoder(verticalPassDesc);

        // Set the pipeline that will be used for this render pass.
        verticalPassEncoder->setRenderPipelineState(m_verticalPassPipeline);
        verticalPassEncoder->setVertexBuffer(m_vertexBuffer, 0, 0);

        // Set texture
        verticalPassEncoder->setFragmentTexture(m_midStepTexture->Texture, 0);
        verticalPassEncoder->setFragmentSamplerState(m_midStepTexture->Sampler, 0);

        verticalPassEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 0, 6, 1);

        verticalPassEncoder->endEncoding();
        verticalPassCommandBuffer->commit();
    }

#pragma endregion
}
