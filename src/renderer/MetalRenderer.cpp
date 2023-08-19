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

        Resize();

        m_framework.Context.MetalDevice = m_device;
    }

    void MetalRenderer::Resize()
    {
        // DEPTH TEXTURE TODO
        // MTL::TextureDescriptor *depthTextureDescriptor = MTL::TextureDescriptor::alloc();
        // depthTextureDescriptor->setDepth
        // depthTextureDescriptor->setTextureType(MTL::TextureType::TextureType2D);
        // depthTextureDescriptor->setPixelFormat(MTL::PixelFormat::PixelFormatDepth32Float);
        // depthTextureDescriptor->setWidth(m_bufferSize.X);
        // depthTextureDescriptor->setHeight(m_bufferSize.Y);
        // depthTextureDescriptor->setDepth(1);
        // depthTextureDescriptor->setMipmapLevelCount(1);
        // depthTextureDescriptor->setArrayLength(1);
        // depthTextureDescriptor->setSampleCount(1);
        // depthTextureDescriptor->setSwizzle(MTL::TextureSwizzle::TextureSwizzleR, MTL::TextureSwizzle::TextureSwizzleZero, MTL::TextureSwizzle::TextureSwizzleZero, MTL::TextureSwizzle::TextureSwizzleOne);
        // depthTextureDescriptor->setUsage(MTL::TextureUsageRenderTarget);

        // m_depthTexture = m_device->newTexture(depthTextureDescriptor);

        // m_drawableSize = m_metalLayer->drawableSize();
        // m_currentDrawable = m_metalLayer->nextDrawable();
        // m_renderPassDescriptor = MTL::RenderPassDescriptor::renderPassDescriptor();
        // m_renderPassDescriptor->colorAttachments()[0]->setTexture(m_currentDrawable->texture());
        // m_renderPassDescriptor->colorAttachments()[0]->setLoadAction(MTL::LoadAction::Clear);
        // m_renderPassDescriptor->colorAttachments()[0]->setClearColor(MTL::ClearColor(0.0, 0.0, 0.0, 1.0));
        // m_renderPassDescriptor->colorAttachments()[0]->setStoreAction(MTL::StoreAction::Store);

    //     const size_t NumVertices = 3;

    //     simd::float3 positions[NumVertices] =
    //         {
    //             {-0.8f, 0.8f, 0.0f},
    //             {0.0f, -0.8f, 0.0f},
    //             {+0.8f, 0.8f, 0.0f}};

    //     simd::float3 colors[NumVertices] =
    //         {
    //             {1.0, 0.3f, 0.2f},
    //             {0.8f, 1.0, 0.0f},
    //             {0.8f, 0.0f, 1.0}};

    //     const size_t positionsDataSize = NumVertices * sizeof(simd::float3);
    //     const size_t colorDataSize = NumVertices * sizeof(simd::float3);

    //     MTL::Buffer *pVertexPositionsBuffer = m_device->newBuffer(positionsDataSize, MTL::ResourceStorageModeManaged);
    //     MTL::Buffer *pVertexColorsBuffer = m_device->newBuffer(colorDataSize, MTL::ResourceStorageModeManaged);

    //     m_positionBuffer = pVertexPositionsBuffer;
    //     m_colorsBuffer = pVertexColorsBuffer;

    //     memcpy(m_positionBuffer->contents(), positions, positionsDataSize);
    //     memcpy(m_colorsBuffer->contents(), colors, colorDataSize);

    //     m_positionBuffer->didModifyRange(NS::Range::Make(0, m_positionBuffer->length()));
    //     m_colorsBuffer->didModifyRange(NS::Range::Make(0, m_colorsBuffer->length()));

    //     float vertices[9] = {
    //         -0.5f, -0.5f, 0.0f, // Vertex 1
    //         0.5f, -0.5f, 0.0f,  // Vertex 2
    //         0.0f, 0.5f, 0.0f    // Vertex 3
    //     };
    //     m_device->newBuffer(&vertices, 3 * 3 * sizeof(float), MTL::CPUCacheModeDefaultCache);

    //     const char *shaderSrc = R"(
    //     #include <metal_stdlib>
    //     using namespace metal;

    //     struct v2f
    //     {
    //         float4 position [[position]];
    //         half3 color;
    //     };

    //     v2f vertex vertexMain( uint vertexId [[vertex_id]],
    //                            device const float3* positions [[buffer(0)]],
    //                            device const float3* colors [[buffer(1)]] )
    //     {
    //         v2f o;
    //         o.position = float4( positions[ vertexId ], 1.0 );
    //         o.color = half3 ( colors[ vertexId ] );
    //         return o;
    //     }

    //     half4 fragment fragmentMain( v2f in [[stage_in]] )
    //     {
    //         return half4( in.color, 1.0 );
    //     }
    // )";

    //     NS::Error *pError = nullptr;
    //     MTL::Library *pLibrary = m_device->newLibrary(NS::String::string(shaderSrc, NS::StringEncoding::UTF8StringEncoding), nullptr, &pError);
    //     if (!pLibrary)
    //     {
    //         __builtin_printf("%s", pError->localizedDescription()->utf8String());
    //         assert(false);
    //     }

    //     MTL::Function *pVertexFn = pLibrary->newFunction(NS::String::string("vertexMain", NS::StringEncoding::UTF8StringEncoding));
    //     MTL::Function *pFragFn = pLibrary->newFunction(NS::String::string("fragmentMain", NS::StringEncoding::UTF8StringEncoding));

    //     MTL::RenderPipelineDescriptor *pDesc = MetalRenderPipelineUtil::CreatePipelineDescriptor(pVertexFn, pFragFn);

    //     m_renderPipelineState = m_device->newRenderPipelineState(pDesc, &pError);
    //     if (!m_renderPipelineState)
    //     {
    //         __builtin_printf("%s", pError->localizedDescription()->utf8String());
    //         assert(false);
    //     }

    //     pVertexFn->release();
    //     pFragFn->release();
    //     pDesc->release();
    //     pLibrary->release();
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

        MTL::CommandQueue *queue = m_device->newCommandQueue();
        m_commandBuffer = queue->commandBuffer();
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
    }
}
