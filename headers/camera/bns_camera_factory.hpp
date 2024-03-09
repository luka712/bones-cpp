#ifndef BNS_CAMERA_FACTORY_HPP

#define BNS_CAMERA_FACTORY_HPP

#include "bns_types.hpp"
#include "camera/bns_perspective_camera.hpp"

namespace bns
{
    class Framework;

    /// @brief The camera factory.
    class CameraFactory
    {
    private:
        Framework *m_framework;

    public:
        /// @brief The constructor for the camera factory.
        /// @param framework The framework.
        CameraFactory(Framework *framework);

        /// @brief Create a perspective camera.
        /// @param fov The field of view. By default 60 degrees. 
        /// @param aspectRatio The aspect ratio. By default 1.0. 
        /// @param nearZ The near plane. By default 0.01.
        /// @param farZ The far plane. By default 100.0.
        /// @return The perspective camera.
        PerspectiveCamera *CreatePerspectiveCamera(f32 fov = 60.0f, f32 aspectRatio = 1.0f, f32 nearZ = 0.01f, f32 farZ = 100.0f);
    };
}

#endif