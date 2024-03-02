#if USE_WEBGPU

#include "camera/bns_webgpu_perspective_camera.hpp"
#include "renderer/bns_webgpu_renderer.hpp"

namespace bns
{
    WebGPUPerspectiveCamera::WebGPUPerspectiveCamera(Renderer *renderer, f32 aspectRatio)
        : PerspectiveCamera(aspectRatio)
    {
        m_renderer = renderer;
        m_device = static_cast<WebGPURenderer *>(m_renderer)->GetDevice();
    }

    void WebGPUPerspectiveCamera::Initialize()
    {
        m_buffer = new WebGPUUniformBuffer<Mat4x4f>(m_renderer);
        m_buffer->Initialize();
        Update();
    }

    void WebGPUPerspectiveCamera::Update()
    {
        UpdateMatrices();
        m_buffer->Update(m_viewProjectionMatrix);
    }

    void WebGPUPerspectiveCamera::Dispose()
    {
        m_buffer->Dispose();
        delete m_buffer;
        m_buffer = nullptr;
    }
}

#endif