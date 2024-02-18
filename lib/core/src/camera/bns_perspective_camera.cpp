#include "camera/bns_perspective_camera.hpp"

namespace bns 
{
    PerspectiveCamera::PerspectiveCamera(f32 aspectRatio)
        : Eye(Vec3f(0.0f, 0.0f, -3.0f)),
          Target(Vec3f(0.0f, 0.0f, 0.0f)),
          Up(Vec3f(0.0f, 1.0f, 0.0f)),
          FieldOfView(1.5708f), // 90 degrees
          AspectRatio(aspectRatio),
          NearPlane(0.1f),
          FarPlane(100.0f)
    {
        UpdateMatrices();
    }

    void PerspectiveCamera::UpdateMatrices()
    {
        m_viewMatrix = Mat4x4f::LookAt(Eye, Target, Up);
        m_projectionMatrix = Mat4x4f::Perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}