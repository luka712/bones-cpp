#if USE_OPENGL

#ifndef BNS_OPENGL_PERSPECTIVE_CAMERA_HPP

#define BNS_OPENGL_PERSPECTIVE_CAMERA_HPP

#include "camera/bns_perspective_camera.hpp"
#include "buffers/bns_opengl_uniform_buffer.hpp"

namespace bns
{
    /// @brief The perspective camera for OpenGL.
    class OpenGLPerspectiveCamera : public PerspectiveCamera
    {
    private:
        OpenGLUniformBuffer<Mat4x4f> *m_buffer;

    public:
        /// @brief Constructor for the perspective camera.
        /// @param fov The field of view of the camera. In degrees.
        /// @param aspectRatio The aspect ratio of the camera.
        /// @param near The near plane of the camera.
        /// @param far The far plane of the camera.
        OpenGLPerspectiveCamera(f32 fov, f32 aspectRatio, f32 nearZ, f32 farZ);

        /// @brief Get the buffer of the camera.
        inline UniformBuffer<Mat4x4f> *GetBuffer() const { return m_buffer; }

        void Initialize() override;
        void Update() override;
        void Dispose() override;
    };
}

#endif

#endif