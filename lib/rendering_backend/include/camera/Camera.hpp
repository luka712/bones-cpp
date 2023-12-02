#pragma once

#ifndef BNS_CAMERA_HPP

#define BNS_CAMERA_HPP

#include "Mat4x4.hpp"

namespace bns
{
    class Camera
    {
    public:
        /**
         * @brief The projection matrix.
         */
        Mat4x4f ProjectionMatrix;

        /**
         * @brief The view matrix.
         */
        Mat4x4f ViewMatrix;

        /// @brief The projection view matrix.
        Mat4x4f ProjectionViewMatrix;

        virtual void Update(f32 deltaTime) = 0;
    };
}

#endif
