#ifndef BNS_MATH_VEC2_H

#define BNS_MATH_VEC2_H

#include "data/Types.hpp"

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

};

#endif