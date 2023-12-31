

// for metal
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include "BnsMetal.hpp"

// for webgpu
#define WEBGPU_CPP_IMPLEMENTATION
#include <webgpu/webgpu.hpp>

#include <iostream>
#include <SDL2/SDL.h>

#include "Framework.hpp"

bns::Framework *engine;

// Scene data
bns::SpriteFont *font;
bns::Texture2D *testTexture;
bns::BloomEffect *effect;

static bns::f32 rotation = 0.0f;

void Initialize();
void Draw();

int main()
{
    bns::FrameworkDescription desc;
    desc.RendererType = bns::RendererType::Vulkan;
    engine = new bns::Framework(desc);

    bns::WindowParameters parameters;
    engine->DrawCallback = [&]()
    { Draw(); };

    engine->Initialize(parameters, Initialize);

    return 0;
}

void Initialize()
{
    return;
    font = engine->GetBitmapSpriteFontLoader().LoadSnowBImpl("assets/SpriteFont.xml", "assets/SpriteFont.png");
    testTexture = engine->GetTextureManager().LoadTexture2D("assets/uv_test.png");

    // effect = engine->GetEffectFactory().CreateBloomEffect();

    bns::Renderer *renderer = engine->GetRenderer();

    //  renderer->SetRenderTexture(effect->GetSourceTexture());
    //  renderer->SetBrightnessTexture(effect->GetBrightnessTexture());

    // engine->GetSpriteRenderer()->PointLights[0].Intensity = 0.0;
    // engine->GetSpriteRenderer()->PointLights[0].Position = bns::Vec3f(50.0f, 50.0f, 100.0f);
    // engine->GetSpriteRenderer()->PointLights[0].Color = bns::Color::Red();
    // engine->GetSpriteRenderer()->PointLights[0].Attenuation.Unit = 100.0f;
    // engine->GetSpriteRenderer()->AmbientLight.Intensity = 0.0f;
    // engine->GetSpriteRenderer()->AmbientLight.Color = bns::Color::Black();
}

void Draw()
{
    return;
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
