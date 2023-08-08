#ifndef BNS_SPRITE_RENDERER_HPP

#define BNS_SPRITE_RENDERER_HPP

#include "textures/Texture2D.hpp"
#include "data/Rect.hpp"
#include "camera/SpriteRendererCamera.hpp"

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
        virtual void Draw(const Texture2D &texture, const Rect &sourceRect) = 0;

        /**
         * To be called when the frame ends.
         */
        virtual void EndFrame() = 0;
    };

}

#endif // !BNS_SPRITE_RENDERER_HPP