#if USE_METAL

#include "camera/bns_metal_perspective_camera.hpp"

namespace bns
{
    MetalPerspectiveCamera::MetalPerspectiveCamera(Renderer *renderer, f32 aspectRatio)
        : PerspectiveCamera(aspectRatio)
    {
        m_renderer = static_cast<MetalRenderer *>(renderer);
        m_device = m_renderer->GetDevice();
    }

    void MetalPerspectiveCamera::Initialize()
    {
        m_buffer = new MetalUniformBuffer<Mat4x4f>(m_renderer, 1, "Perspective Camera Buffer");
        m_buffer->Initialize();
        Update();
    }

    void MetalPerspectiveCamera::Update()
    {
        UpdateMatrices();
        m_buffer->Update(m_viewProjectionMatrix);
    }

    void MetalPerspectiveCamera::Dispose()
    {
        m_buffer->Dispose();
        delete m_buffer;
        m_buffer = nullptr;
    }
}

#endif