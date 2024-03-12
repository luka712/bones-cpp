#include "camera/bns_camera_factory.hpp"
#include "bns_framework.hpp"
#include "bns_math.hpp"

#if USE_WEBGPU
#include "camera/bns_webgpu_perspective_camera.hpp"
#endif

#if USE_METAL
#include "camera/bns_metal_perspective_camera.hpp"
#endif

#if USE_OPENGL
#include "camera/bns_opengl_perspective_camera.hpp"
#endif

namespace bns
{
    CameraFactory::CameraFactory(Framework *framework)
        : m_framework(framework)
    {
    }

    PerspectiveCamera *CameraFactory::CreatePerspectiveCamera(f32 fov, f32 aspectRatio, f32 nearZ, f32 farZ)
    {
        PerspectiveCamera *camera = nullptr;
        fov = ToRadians(fov);

#if USE_WEBGPU
        if (m_framework->GetRendererType() == RendererType::WebGPU)
        {
            camera = new WebGPUPerspectiveCamera(m_framework->GetRenderer(), fov, aspectRatio, nearZ, farZ);
        }
#endif

#if USE_METAL
        if (m_framework->GetRendererType() == RendererType::Metal)
        {
            camera = new MetalPerspectiveCamera(m_framework->GetRenderer(), fov, aspectRatio, nearZ, farZ);
        }
#endif

#if USE_OPENGL
        if (m_framework->GetRendererType() == RendererType::OpenGL)
        {
            camera = new OpenGLPerspectiveCamera(fov, aspectRatio, nearZ, farZ);
        }
#endif

        camera->Initialize();

        return camera;
    }
}
