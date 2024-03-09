#if USE_OPENGL

#include "camera/bns_opengl_perspective_camera.hpp"
#include "renderer/bns_opengl_renderer.hpp"

namespace bns
{
    OpenGLPerspectiveCamera::OpenGLPerspectiveCamera(f32 fov, f32 aspectRatio, f32 nearZ, f32 farZ)
        : PerspectiveCamera(fov, aspectRatio, nearZ, farZ)
    {
    }

    void OpenGLPerspectiveCamera::Initialize()
    {
        m_buffer = new OpenGLUniformBuffer<Mat4x4f>();
        m_buffer->Initialize();
        Update();
    }

    void OpenGLPerspectiveCamera::Update()
    {
        UpdateMatrices();
        m_buffer->Update(m_viewProjectionMatrix);
    }

    void OpenGLPerspectiveCamera::Dispose()
    {
        m_buffer->Dispose();
        delete m_buffer;
        m_buffer = nullptr;
    }
}

#endif