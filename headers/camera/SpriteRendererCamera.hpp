#ifndef BNS_SPRITE_RENDERER_CAMERA_HPP

#define BNS_SPRITE_RENDERER_CAMERA_HPP

#include "camera/Camera.hpp"

namespace bns 
{
    /**
     * @brief The sprite renderer camera.
    */
    class SpriteRendererCamera final : public Camera
    {
        public:
            SpriteRendererCamera();
            SpriteRendererCamera(i32 width, i32 height);
            void Update(f32 deltaTime) override;
    };
}

#endif 