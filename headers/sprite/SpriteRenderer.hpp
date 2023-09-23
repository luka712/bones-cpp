#ifndef BNS_SPRITE_RENDERER_HPP

#define BNS_SPRITE_RENDERER_HPP

#include <string>
#include "textures/Texture2D.hpp"
#include "data/Color.hpp"
#include "data/Rect.hpp"
#include "data/Vec2.hpp"
#include "camera/SpriteRendererCamera.hpp"
#include "font/SpriteFont.hpp"

namespace bns
{
    /**
     * @brief The sprite renderer.
     */
    class SpriteRenderer
    {
    protected:
        SpriteRendererCamera m_camera;

    public:
        /**
         * @brief Initialize the sprite renderer.
         */
        virtual void Initialize() = 0;

        /**
         * To be called when the frame begins.
         */
        virtual void BeginFrame() = 0;

        /**
         * Draw a texture at a position indicated by the rect.
         * @param texture The texture to draw.
         * @param rect The rect that indicates the position and size.
         */
        void Draw(Texture2D *texture, const Rect &drawRect);

        /**
         * Draw a texture at a position indicated by the rect. The source rect indicates the part of the texture to draw.
         * @param texture The texture to draw.
         * @param drawRect The rect that indicates the position and size.
         * @param sourceRect The rect that indicates the part of the texture to draw.
         */
        void Draw(Texture2D *texture, const Rect &drawRect, const Rect &sourceRect);

        /**
         * Draw a texture at a position indicated by the rect. The source rect indicates the part of the texture to draw.
         * @param texture The texture to draw.
         * @param drawRect The rect that indicates the position and size.
         * @param sourceRect The rect that indicates the part of the texture to draw.
         * @param tintColor The tint color.
         */
        virtual void Draw(Texture2D *texture,
                          const Rect &drawRect,
                          const Rect &sourceRect,
                          const Color &tintColor,
                          f32 rotationInRadians,
                          const Vec2f &rotationOrigin) = 0;

        /**
         * @brief Draw a string.
         * @param font The font to use.
         * @param text The text to draw.
         * @param position The position to draw at.
         * @param color The color to draw with.
         * @param scale The scale to draw with.
         */
        virtual void DrawString(SpriteFont *font,
                                const std::string &text,
                                const Vec2f &position,
                                const Color &color,
                                const f32 scale) = 0;

        /**
         * To be called when the frame ends.
         */
        virtual void EndFrame() = 0;
    };

}

#endif // !BNS_SPRITE_RENDERER_HPP