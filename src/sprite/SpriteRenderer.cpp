#include "sprite/SpriteRenderer.hpp"

namespace bns
{
    void SpriteRenderer::Draw(Texture2D *texture, const Rect &drawRect)
    {
        Rect sourceRect(0, 0, texture->GetWidth(), texture->GetHeight());
        Color color = Color::White();
        Draw(texture, drawRect, sourceRect, color);
    }

    void SpriteRenderer::Draw(Texture2D *texture, const Rect &drawRect, const Rect &sourceRect)
    {
        Color color = Color::White();
        Draw(texture, drawRect, sourceRect, color);
    }
}