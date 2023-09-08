#include "renderer/MetalRenderer.hpp"
#include <simd/simd.h>
#include "util/MetalUtil.hpp"
#include "Framework.hpp"

namespace bns
{
    MetalRenderer::MetalRenderer(Framework &framework)
        : m_framework(framework)
    {
        ClearColor = Color::LightPink();
    }

    void MetalRenderer::Initialize(CA::MetalLayer *metalLayer)
    {
        m_metalLayer = metalLayer;

        m_bufferSize = Vec2f(m_metalLayer->drawableSize().width, m_metalLayer->drawableSize().height);

        m_device = m_metalLayer->device();
        m_queue = m_device->newCommandQueue();

        Resize();

        m_framework.Context.MetalDevice = m_device;
    }

    void MetalRenderer::Resize()
    {
        
    }

    void MetalRenderer::BeginDraw()
    {
        // Render or update your game/application here
        m_currentDrawable = m_metalLayer->nextDrawable();

        MTL::ClearColor clearColor(ClearColor.R, ClearColor.G, ClearColor.B, 1.0);

        MTL::RenderPassDescriptor *pass = MTL::RenderPassDescriptor::renderPassDescriptor();

        MTL::RenderPassColorAttachmentDescriptor *colorAttachment = pass->colorAttachments()->object(0);
        colorAttachment->setClearColor(clearColor);
        colorAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
        colorAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
        colorAttachment->setTexture(m_currentDrawable->texture());

        // MTL::RenderPassDepthAttachmentDescriptor *depthAttachment = pass->depthAttachment();
        // depthAttachment->setTexture(m_depthTexture);
        // depthAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
        // depthAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
        // depthAttachment->setClearDepth(1.0);

        // MTL::RenderPassStencilAttachmentDescriptor *stencilAttachment = pass->stencilAttachment();
        // stencilAttachment->setTexture(m_depthTexture);
        // stencilAttachment->setLoadAction(MTL::LoadAction::LoadActionClear);
        // stencilAttachment->setStoreAction(MTL::StoreAction::StoreActionStore);
        // stencilAttachment->setClearStencil(0);

    
        m_commandBuffer = m_queue->commandBuffer();
        m_renderCommandEncoder = m_commandBuffer->renderCommandEncoder(pass);
        m_framework.Context.CurrentMetalRenderCommandEncoder = m_renderCommandEncoder;
        // MTL::ResourceStateCommandEncoder *updateEncoder = m_commandBuffer->resourceStateCommandEncoder();

        // viewport
        m_renderCommandEncoder->setViewport(MTL::Viewport{
            0.0f, 0.0f,
            (double)m_bufferSize.X, m_bufferSize.Y,
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
    }

    void MetalRenderer::EndDraw()
    {
        m_renderCommandEncoder->endEncoding();
        m_commandBuffer->presentDrawable(m_currentDrawable);
        m_commandBuffer->commit();
        
        m_commandBuffer->release();
        m_renderCommandEncoder->release();
    }
}
