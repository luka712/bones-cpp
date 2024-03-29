#if USE_METAL

#include "effects/metal/MetalTextureCombineEffect.hpp"
#include "bns_framework.hpp"
#include "bns_metal_util.hpp"

namespace bns
{

    #pragma region Implementation

    MetalTextureCombineEffectImpl::MetalTextureCombineEffectImpl(const Framework &framework)
        : MetalEffectImpl(framework)
    {
        m_mixValue = 0.5;
    }

    void MetalTextureCombineEffectImpl::Initialize()
    {
        MTL::Device* device = m_renderer->GetDevice();
        
        MetalEffectImpl::Initialize();
        
        m_mixValueBuffer = MetalUtil::Buffer.Create(m_device, sizeof(f32), "texture_combine_mix_value_buffer");
    }

    void MetalTextureCombineEffectImpl::Draw(void *destinationTexture)
    {
        MTL::CommandQueue *queue = m_renderer->GetCommandQueue();

        // Convert to Metal types
        MetalTexture2D* mtlTextureWrapper = static_cast<MetalTexture2D*>(m_sourceTexture);
        MTL::Texture* mtlDestTexture = static_cast<MTL::Texture*>(destinationTexture);
        
         // TODO: this can be written when value is set! (not every frame)
        // Write to mix value
        memcpy(m_mixValueBuffer->contents(), &m_mixValue, sizeof(f32));

        MTL::CommandBuffer* commandBuffer = queue->commandBuffer();
        
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
        
        // Set mix value buffer
        pEncoder->setFragmentBuffer(m_mixValueBuffer, 0, 0);

        // set textures
        pEncoder->setFragmentTexture(mtlTextureWrapper->Texture, 0);
        pEncoder->setFragmentSamplerState(mtlTextureWrapper->Sampler, 0);
        pEncoder->setFragmentTexture(m_combineTexture->Texture, 1);
        pEncoder->setFragmentSamplerState(m_combineTexture->Sampler, 1);

        pEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 0,6,1);

        pEncoder->endEncoding();
        commandBuffer->commit();
    }

#pragma endregion

} // namespace bns


#endif //  __APPLE__
