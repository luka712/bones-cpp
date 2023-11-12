#ifndef BNS_FREE_CAMERA_HPP

#define BNS_FREE_CAMERA_HPP

#include "Camera.hpp"

namespace bns
{
    class FreeCamera : public Camera
    {
private:
    Vec3f m_right;
    Vec3f m_forward;
    Vec3f m_up;
    Vec3f m_worldUp;

    public:
        /**
         * @brief The position of the camera.
         */
        Vec3f Position;

        /**
         * The turn speed of the camera.
         */
        f32 TurnSpeed;

        /**
         * The move speed of the camera.
         */
        f32 MoveSpeed;

        FreeCamera();

        void Update(f32 deltaTime) override;
    };

}

#endif