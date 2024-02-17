#include "sprite/bns_sprite_renderer.hpp"
#include "Framework.hpp"

namespace bns
{
    SpriteRenderer::SpriteRenderer()
    {
        for(size_t i = 0; i < FORWARD_2D_NUM_OF_POINT_LIGHTS; i++)
        {
            PointLights[i] = PointLight::AsSpriteLight();
            PointLights[i].Intensity = 0.0f; // turn off all lights by default
        }
    }

    void SpriteRenderer::Draw(Texture2D *texture, const Rect &drawRect)
    {
        Rect sourceRect(0, 0, texture->GetWidth(), texture->GetHeight());
        Color color = Color::White();
        Vec2f rotationOrigin = Vec2f::Zero();
        Draw(texture, drawRect, sourceRect, color, 0.0f, rotationOrigin);
    }

    void SpriteRenderer::Draw(Texture2D *texture, const Rect &drawRect, const Rect &sourceRect)
    {
        Color color = Color::White();
        Vec2f rotationOrigin = Vec2f::Zero();
        Draw(texture, drawRect, sourceRect, color, 0.0f, rotationOrigin);
    }
}