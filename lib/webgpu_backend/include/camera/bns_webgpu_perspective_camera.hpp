#if USE_WEBGPU

#ifndef BNS_WEBGPU_PERSPECTIVE_CAMERA_HPP

#define BNS_WEBGPU_PERSPECTIVE_CAMERA_HPP

#include "renderer/bns_renderer.hpp"
#include "camera/bns_perspective_camera.hpp"
#include "bns_webgpu.hpp"
#include "buffers/bns_webgpu_uniform_buffer.hpp"

namespace bns
{
    /// @brief The perspective camera for WebGPU.
    class WebGPUPerspectiveCamera : public PerspectiveCamera
    {
    private:
        Renderer *m_renderer;
        WGPUDevice m_device;
        WebGPUUniformBuffer<Mat4x4f> *m_buffer;

    public:
        /// @brief Constructor for the perspective camera.
        /// @param renderer The renderer.
        /// @param fov The field of view of the camera. In degrees.
        /// @param aspectRatio The aspect ratio of the camera.
        /// @param near The near plane of the camera.
        /// @param far The far plane of the camera.
        WebGPUPerspectiveCamera(Renderer *renderer, f32 fov, f32 aspectRatio, f32 near, f32 far);

        /// @brief Get the buffer of the camera.
        inline UniformBuffer<Mat4x4f> *GetBuffer() const override { return m_buffer; }

        void Initialize() override;
        void Update() override;
        void Dispose() override;
    };
}

#endif

#endif
