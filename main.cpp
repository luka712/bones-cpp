

// for metal
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include "bns_metal.hpp"

// for webgpu
// #define WEBGPU_CPP_IMPLEMENTATION
// #include <webgpu/webgpu.hpp>

#include <iostream>
#include <SDL2/SDL.h>

#include "Framework.hpp"

#include "pipelines/bns_webgpu_unlit_render_pipeline.hpp"
#include "camera/bns_webgpu_perspective_camera.hpp"
#include "texture/bns_webgpu_texture2d.hpp"
#include "geometry/bns_geometry_builder.hpp"

#include "pipelines/bns_metal_unlit_render_pipeline.hpp"
#include "buffers/bns_metal_vertex_buffer.hpp"
#include "math/bns_mat4x4.hpp"
#include "buffers/bns_metal_uniform_buffer.hpp"
#include "camera/bns_metal_perspective_camera.hpp"

bns::Framework *engine;

// Scene data
bns::SpriteFont *font;
bns::Texture2D *testTexture;
bns::BloomEffect *effect;

#if USE_WEBGPU
bns::WebGPUUnlitRenderPipeline *testPipeline;
bns::WebGPUPerspectiveCamera *testCamera;
bns::WebGPUUniformBuffer<bns::Mat4x4f> *testTransformBuffer;
bns::WebGPUVertexBuffer *testVertexBuffer;
bns::WebGPUIndexBuffer *testIndexBuffer;
#endif

#if USE_METAL
bns::MetalUnlitRenderPipeline *testPipeline;
bns::MetalPerspectiveCamera *testCamera;
bns::MetalVertexBuffer *testVertexBuffer;
bns::MetalIndexBuffer *testIndexBuffer;
#endif

static bns::f32 rotation = 0.0f;

void Initialize();
void Draw();

int main()
{
    bns::FrameworkDescription desc;
    desc.RendererType = bns::RendererType::WebGPU;
    engine = new bns::Framework(desc);

    bns::WindowParameters parameters;
    engine->DrawCallback = [&]()
    { Draw(); };

    engine->Initialize(parameters, Initialize);
    engine->Destroy();

    return 0;
}

void Initialize()
{
    font = engine->GetBitmapSpriteFontLoader().LoadSnowBImpl("assets/SpriteFont.xml", "assets/SpriteFont.png");
    bns::TextureOptions options;
    options.Format = bns::TextureFormat::BGRA_8_Unorm;
    options.MagFilter = bns::SamplerMagFilter::NEAREST;
    options.MinFilter = bns::SamplerMinFilter::NEAREST;
    testTexture = engine->GetTextureManager().LoadTexture2D("assets/uv_test.png", "", &options);

    // effect = engine->GetEffectFactory().CreateBloomEffect();

    bns::Renderer *renderer = engine->GetRenderer();

    bns::Geometry geometry = bns::GeometryBuilder().QuadGeomtry();

    //  renderer->SetRenderTexture(effect->GetSourceTexture());
    //  renderer->SetBrightnessTexture(effect->GetBrightnessTexture());

    // engine->GetSpriteRenderer()->PointLights[0].Intensity = 0.0;
    // engine->GetSpriteRenderer()->PointLights[0].Position = bns::Vec3f(50.0f, 50.0f, 100.0f);
    // engine->GetSpriteRenderer()->PointLights[0].Color = bns::Color::Red();
    // engine->GetSpriteRenderer()->PointLights[0].Attenuation.Unit = 100.0f;
    // engine->GetSpriteRenderer()->AmbientLight.Intensity = 0.0f;
    // engine->GetSpriteRenderer()->AmbientLight.Color = bns::Color::Black();
    

#if USE_WEBGPU
    testCamera = new bns::WebGPUPerspectiveCamera(renderer, 800.0f / 600.0f);
    testCamera->Initialize();
    testTransformBuffer = new bns::WebGPUUniformBuffer<bns::Mat4x4f>(renderer);
    testTransformBuffer->Initialize();
    bns::Mat4x4f transform = bns::Mat4x4f::Identity();
    testTransformBuffer->Update(transform);
    testPipeline = new bns::WebGPUUnlitRenderPipeline(renderer, testCamera->GetBuffer(), testTransformBuffer);
    testPipeline->Initialize();

    testVertexBuffer = new bns::WebGPUVertexBuffer(renderer, "Attribute Buffer");
    std::vector<bns::f32> data = geometry.ToInterleaved(bns::GeometryFormat::Pos3_Color4_TextureCoords2);
    testVertexBuffer->Initialize(data, true);
    testVertexBuffer->Update(data);

    testIndexBuffer = new bns::WebGPUIndexBuffer(renderer, "Index Buffer");
    testIndexBuffer->Initialize(geometry.Indices);

#endif
    


#if USE_METAL
    testCamera = new bns::MetalPerspectiveCamera(renderer, 800.0f / 600.0f);
    testCamera->Initialize();

    auto modelBuffer = new bns::MetalUniformBuffer<bns::Mat4x4f>(renderer, 1, "Model Buffer");
    modelBuffer->Initialize();
    auto transform = bns::Mat4x4f::Identity();
    modelBuffer->Update(transform);

    testPipeline = new bns::MetalUnlitRenderPipeline(renderer, static_cast<bns::MetalUniformBuffer<bns::Mat4x4f>*>(testCamera->GetBuffer()), modelBuffer);
    testPipeline->Initialize();

    testVertexBuffer = new bns::MetalVertexBuffer(renderer, "Attribute Buffer");
    std::vector<bns::f32> data = geometry.ToInterleaved(bns::GeometryFormat::Pos3_Color4_TextureCoords2);
    testVertexBuffer->Initialize(data, true);
    testVertexBuffer->Update(data);

    testIndexBuffer = new bns::MetalIndexBuffer(renderer, "Index Buffer");
    testIndexBuffer->Initialize(geometry.Indices);
#endif
}

void Draw()
{
    bns::Event event;
    if (engine->GetEvents().HasEvent(bns::EventType::KeyDown, &event))
    {
        if (engine->GetCurrentRenderer() == bns::RendererType::Metal)
        {
            // engine->SwitchRenderer(bns::RendererType::OpenGL);
        }
        else if (engine->GetCurrentRenderer() == bns::RendererType::OpenGL)
        {
            // engine->SwitchRenderer(bns::RendererType::Metal);
        }
    }

    bns::Renderer *renderer = engine->GetRenderer();
    bns::SpriteRenderer *spriteRenderer = engine->GetSpriteRenderer();

    bns::i32 hw = testTexture->GetWidth() / 2;
    bns::i32 hh = testTexture->GetHeight() / 2;

    rotation += 0.001;
    bns::Vec2f rotationOrigin = bns::Vec2f(0.5f, 0.5f);

    //     testPipeline->Render(*testVertexBuffer, *testIndexBuffer);

    engine->GetSpriteRenderer()->PointLights[0].Intensity += 0.1f;
    spriteRenderer->DrawString(font, "Hello World!", bns::Vec2f(300, 300), bns::Color::White(), 1.0f);

    // whole texture
    spriteRenderer->Draw(testTexture, bns::Rect(0, 0, 100, 100));

    // top left quadrant
    spriteRenderer->Draw(testTexture, bns::Rect(100, 0, 100, 100), bns::Rect(0, 0, hw, hh), bns::Color::White(), rotation, rotationOrigin);

    // top right quadrant
    spriteRenderer->Draw(testTexture, bns::Rect(200, 0, 100, 100), bns::Rect(hw, 0, hw, hh), bns::Color::White(), rotation, rotationOrigin);

    // bottom left quadrant
    spriteRenderer->Draw(testTexture, bns::Rect(100, 100, 100, 100), bns::Rect(0, hh, hw, hh), bns::Color::White(), rotation, rotationOrigin);

    // bottom right quadrant
    spriteRenderer->Draw(testTexture, bns::Rect(200, 100, 100, 100), bns::Rect(hw, hh, hw, hh), bns::Color::White(), rotation, rotationOrigin);



    // effect->Draw(renderer->GetSwapChainTexture());
}
