#include "effects/metal/MetalBloomEffect.hpp"
#include "Framework.hpp"
#include "util/MetalUtil.hpp"

namespace bns
{

#pragma region Implementation

    MetalBloomEffectImpl::MetalBloomEffectImpl(const Framework &framework)
        : MetalEffectImpl(framework), m_blurEffect(framework)
    {
        BrightnessBlurPasses = 3;
    }

    void MetalBloomEffectImpl::Initialize()
    {
        MTL::Device *device = m_framework.Context.MetalDevice;

        auto bufferSize = m_framework.GetRenderer()->GetBufferSize();

        auto tex = m_framework.GetTextureManager().CreateEmpty(
            bufferSize.X, bufferSize.Y,
            TextureUsage::TEXTURE_BINDING | TextureUsage::COPY_DST | TextureUsage::RENDER_ATTACHMENT,
            TextureFormat::BGRA_8_Unorm);

        m_brightnessTexture = static_cast<MetalTexture2D *>(tex);

        MetalEffectImpl::Initialize();
        m_blurEffect.Initialize();
        m_blurEffect.SetSourceTexture(m_brightnessTexture);
    }

    void MetalBloomEffectImpl::Draw(void *destinationTexture)
    {
        for (u32 i = 0; i < BrightnessBlurPasses; i++)
        {
            m_blurEffect.Draw(m_brightnessTexture->Texture);
        }

        MTL::Device *device = m_framework.Context.MetalDevice;
        MTL::CommandQueue *queue = m_framework.Context.MetalCommandQueue;

        // Convert to Metal types
        MetalTexture2D *mtlTextureWrapper = static_cast<MetalTexture2D *>(m_sourceTexture);
        MTL::Texture *mtlDestTexture = static_cast<MTL::Texture *>(destinationTexture);

        MTL::CommandBuffer *commandBuffer = queue->commandBuffer();

        // Create a command pEncoder which can be used to submit GPU operations.
        MTL::RenderPassDescriptor *pRenderPassDesc = MTL::RenderPassDescriptor::renderPassDescriptor();

        // Set the color attachment texture as the destination texture.
        MTL::RenderPassColorAttachmentDescriptor *colorAttachment = pRenderPassDesc->colorAttachments()->object(0);
        colorAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
        colorAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
        colorAttachment->setTexture(mtlDestTexture);

        MTL::RenderCommandEncoder *pEncoder = commandBuffer->renderCommandEncoder(pRenderPassDesc);

        // Set the pipeline that will be used for this render pass.
        pEncoder->setRenderPipelineState(m_pipeline);

        // set vertex buffer
        pEncoder->setVertexBuffer(m_vertexBuffer, 0, 0);

        // set textures
        pEncoder->setFragmentTexture(mtlTextureWrapper->Texture, 0);
        pEncoder->setFragmentSamplerState(mtlTextureWrapper->Sampler, 0);
        pEncoder->setFragmentTexture(m_brightnessTexture->Texture, 1);
        pEncoder->setFragmentSamplerState(m_brightnessTexture->Sampler, 1);

        pEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 0, 6, 1);

        pEncoder->endEncoding();
        commandBuffer->commit();
    }

#pragma endregion

} // namespace bns
