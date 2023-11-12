#include "camera/SpriteRendererCamera.hpp"

namespace bns
{
    SpriteRendererCamera::SpriteRendererCamera()
    {
    }

    void SpriteRendererCamera::Initialize(i32 width, i32 height)
    {
        ProjectionMatrix = Mat4x4f::Orthographic(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    }

    void SpriteRendererCamera::Update(f32 deltaTime)
    {
        ProjectionViewMatrix = ProjectionMatrix;
    }
}
