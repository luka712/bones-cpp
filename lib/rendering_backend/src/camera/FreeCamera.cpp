#include "camera/FreeCamera.hpp"
#include "bns_math.hpp"

namespace bns
{
    FreeCamera::FreeCamera()
    {
        Position = Vec3f(0.0f, 0.0f, 3.0f);

        m_right = Vec3f::UnitX();
        m_forward = Vec3f::UnitZ();
        m_up = Vec3f::Zero();
        m_worldUp = Vec3f::UnitY();

        ProjectionMatrix = Mat4x4f::Perspective(ToRadians(90.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
        ViewMatrix = Mat4x4f::LookAt(Position, Position + m_forward, m_up);
    }

    void FreeCamera::Update(f32 deltaTime)
    {
        ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;
    }
}