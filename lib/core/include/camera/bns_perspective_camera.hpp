#ifndef BNS_PERSPECTIVE_CAMERA

#define BNS_PERSPECTIVE_CAMERA

#include "math/bns_mat4x4.hpp"
#include "math/bns_vec3.hpp"
#include "buffers/bns_uniform_buffer.hpp"

namespace bns
{
    class PerspectiveCamera
    {
    protected:
        Mat4x4f m_projectionMatrix;
        Mat4x4f m_viewMatrix;
        Mat4x4f m_viewProjectionMatrix;

        /// @brief Update the matrices of the camera.
        void UpdateMatrices();

    public:
        /// @brief The constructor for the perspective camera.
        /// @param fov The field of view. In degrees.
        /// @param aspectRatio The aspect ratio.
        /// @param near The near plane.
        /// @param far The far plane.
        PerspectiveCamera(f32 fov, f32 apectRatio, f32 near, f32 far);

        /// @brief Get the camera buffer.
        /// @return The camera buffer.
        virtual UniformBuffer<Mat4x4f> *GetBuffer() const = 0;

        /// @brief The eye position of the camera.
        Vec3f Eye;

        /// @brief The target position of the camera.
        Vec3f Target;

        /// @brief The up vector of the camera.
        Vec3f Up;

        /// @brief The field of view of the camera.
        f32 FieldOfView;

        /// @brief The aspect ratio of the camera.
        f32 AspectRatio;

        /// @brief The near plane of the camera.
        f32 NearPlane;

        /// @brief The far plane of the camera.
        f32 FarPlane;

        /// @brief Initialize the camera.
        virtual void Initialize() = 0;

        /// @brief Update the camera.
        virtual void Update() = 0;

        /// @brief Dispose the camera.
        virtual void Dispose() = 0;
    };
}

#endif