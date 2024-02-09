#ifndef BNS_MATH_VEC2_H

#define BNS_MATH_VEC2_H

#include "bns_types.hpp"
#include <math.h>

namespace bns
{
    /**
     * @brief The vector 2 struct.
     *
     * @tparam T - which number type.
     */
    template <typename T>
    struct Vec2
    {
        T X;
        T Y;

        Vec2<T>()
        {
            X = 0;
            Y = 0;
        }
        Vec2<T>(T x, T y) : X(x), Y(y) {}

        /**
         * @brief Get the magnitude of a vector.
         *
         * @return T
         */
        T Magnitude() const
        {
            return sqrt(X * X + Y * Y);
        }

        /**
         * @brief Normalize self.
         *
         */
        void Normalize()
        {
            T l = Magnitude();
            X /= l;
            Y /= l;
        }

        /**
         * @brief Rotate self around the the point.
         * @param point - the point to rotate around.
         * @param theta - the angle in radians.
         * @return void
         */
        void RotateAroundPoint(Vec2<T> point, f32 theta)
        {
            // cos and sin of theta
            f32 c = cos(theta);
            f32 s = sin(theta);

            // origin x and y of the point
            f32 ox = point.X;
            f32 oy = point.Y;

            // rotate point
            f32 rx = c * (X - ox) - s * (Y - oy) + ox;
            f32 ry = s * (X - ox) + c * (Y - oy) + oy;

            // set self to rotated point
            X = rx;
            Y = ry;
        }

        /**
         * Returns the zero vector.
         */
        static Vec2<T> Zero()
        {
            return Vec2<T>(0, 0);
        }
    };

    template <typename T>
    Vec2<T> operator+(const Vec2<T> &a, const Vec2<T> &b)
    {
        return Vec2<T>(a.X + b.X, a.Y + b.Y);
    }

    template <typename T>
    Vec2<T> operator-(const Vec2<T> &a, const Vec2<T> &b)
    {
        return Vec2<T>(a.X - b.X, a.Y - b.Y);
    }

    template <typename T>
    Vec2<T> operator*(const Vec2<T> &a, const Vec2<T> &b)
    {
        return Vec2<T>(a.X * b.X, a.Y * b.Y);
    }

    template <typename T>
    Vec2<T> operator/(const Vec2<T> &a, const Vec2<T> &b)
    {
        return Vec2<T>(a.X / b.X, a.Y / b.Y);
    }

    template <typename T>
    bool operator==(const Vec2<T> &a, const Vec2<T> &b)
    {
        return a.X == b.X && a.Y == b.Y;
    }

    template <typename T>
    bool operator!=(const Vec2<T> &a, const Vec2<T> &b)
    {
        return a.X != b.X || a.Y != b.Y;
    }

    typedef Vec2<f32> Vec2f;
    typedef Vec2<i32> Vec2i;
    typedef Vec2<u32> Vec2u;

};

#endif