#include "renderer/metal/MetalRenderer.hpp"
#include <simd/simd.h>
#include "util/MetalUtil.hpp"
#include "Framework.hpp"
#include "texture/MetalTexture2D.hpp"

namespace bns
{
MetalRenderer::MetalRenderer(Framework &framework)
: Renderer(framework)
{
 
}

/**
 * @brief Gets the view into swap chain texture.
 */
void* MetalRenderer::GetSwapChainTexture()
{
    return m_currentDrawable->texture();
}

void MetalRenderer::Initialize(CA::MetalLayer *metalLayer)
{
    m_metalLayer = metalLayer;
    
    m_bufferSize = m_framework.GetWindowManager().GetWindowSize();
    
    m_device = m_metalLayer->device();
    m_queue = m_device->newCommandQueue();
    
    Resize();
    
    m_framework.Context.MetalDevice = m_device;
    m_framework.Context.MetalCommandQueue = m_queue;
}

void MetalRenderer::Resize()
{
    
}

void MetalRenderer::BeginDraw()
{
    // Render or update your game/application here
    m_currentDrawable = m_metalLayer->nextDrawable();
    
    MTL::ClearColor clearColor(ClearColor.R, ClearColor.G, ClearColor.B, 1.0);
    
    MTL::RenderPassDescriptor *pRenderPassDesc = MTL::RenderPassDescriptor::renderPassDescriptor();
    
    // Get texture from current drawable or if there is render texture use that instead.
    MTL::Texture* drawToTexture = m_currentDrawable->texture();
    if(m_renderTexture != nullptr)
    {
        MTL::Texture* mtlTexture = static_cast<MetalTexture2D*>(m_renderTexture)->Texture;
        drawToTexture = mtlTexture;
    }
    
    MTL::RenderPassColorAttachmentDescriptor *colorAttachment = pRenderPassDesc->colorAttachments()->object(0);
    colorAttachment->setClearColor(clearColor);
    colorAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
    colorAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
    colorAttachment->setTexture(drawToTexture);

    // if there is a brightness texture, use that as well as a second color attachment
    if(m_brightnessTexture != nullptr)
    {
        MTL::Texture* mtlTexture = static_cast<MetalTexture2D*>(m_brightnessTexture)->Texture;
        MTL::RenderPassColorAttachmentDescriptor *colorAttachment2 = pRenderPassDesc->colorAttachments()->object(1);
        colorAttachment2->setClearColor(clearColor);
        colorAttachment2->setLoadAction(MTL::LoadAction::LoadActionClear);
        colorAttachment2->setStoreAction(MTL::StoreAction::StoreActionStore);
        colorAttachment2->setTexture(mtlTexture);   
    }
    
    // MTL::RenderPassDepthAttachmentDescriptor *depthAttachment = pRenderPassDesc->depthAttachment();
    // depthAttachment->setTexture(m_depthTexture);
    // depthAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
    // depthAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
    // depthAttachment->setClearDepth(1.0);
    
    // MTL::RenderPassStencilAttachmentDescriptor *stencilAttachment = pRenderPassDesc->stencilAttachment();
    // stencilAttachment->setTexture(m_depthTexture);
    // stencilAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
    // stencilAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
    // stencilAttachment->setClearStencil(0);
    
    
    m_commandBuffer = m_queue->commandBuffer();
    m_renderCommandEncoder = m_commandBuffer->renderCommandEncoder(pRenderPassDesc);
    m_framework.Context.CurrentMetalRenderCommandEncoder = m_renderCommandEncoder;
    // MTL::ResourceStateCommandEncoder *updateEncoder = m_commandBuffer->resourceStateCommandEncoder();
    
    // viewport
    m_renderCommandEncoder->setViewport(MTL::Viewport{
        0.0f, 0.0f,
        (double)m_bufferSize.X, (double)m_bufferSize.Y,
        0.0f, 1.0f});
    
    // scissor test
    MTL::ScissorRect scissorRect;
    scissorRect.x = 0;
    scissorRect.y = 0;
    scissorRect.width = (NS::Integer)m_bufferSize.X;
    scissorRect.height = (NS::Integer)m_bufferSize.Y;
    m_renderCommandEncoder->setScissorRect(scissorRect);
    
    // m_renderCommandEncoder->setRenderPipelineState(m_renderPipelineState);
    // m_renderCommandEncoder->setVertexBuffer(m_positionBuffer, 0, 0);
    // m_renderCommandEncoder->setVertexBuffer(m_colorsBuffer, 0, 1);
    // m_renderCommandEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));
    
    pRenderPassDesc->release();
}

void MetalRenderer::EndDraw()
{
    m_renderCommandEncoder->endEncoding();
    m_commandBuffer->presentDrawable(m_currentDrawable);
    m_commandBuffer->commit();
    
    m_commandBuffer->release();
    m_renderCommandEncoder->release();
}

void MetalRenderer::Destroy()
{
    
}
}
