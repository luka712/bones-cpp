#include "camera/bns_perspective_camera.hpp"
#include "bns_math.hpp"

namespace bns
{
    PerspectiveCamera::PerspectiveCamera(f32 fov, f32 aspectRatio, f32 near, f32 far)
        : Eye(Vec3f(0.0f, 0.0f, -3.0f)),
          Target(Vec3f(0.0f, 0.0f, 0.0f)),
          Up(Vec3f(0.0f, 1.0f, 0.0f))
    {
        FieldOfView = fov;
        AspectRatio = aspectRatio;
        NearPlane = near;
        FarPlane = far;
        UpdateMatrices();
    }

    void PerspectiveCamera::UpdateMatrices()
    {
        m_viewMatrix = Mat4x4f::LookAt(Eye, Target, Up);
        m_projectionMatrix = Mat4x4f::Perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}