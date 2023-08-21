#include "sprite/SpriteRenderer.hpp"

namespace bns
{
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