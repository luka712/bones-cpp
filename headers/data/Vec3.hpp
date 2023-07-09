#ifndef BNS_MATH_VEC3_H

#define BNS_MATH_VEC3_H

#include <math.h>
#include "Types.hpp"

namespace bns
{
    /**
     * @brief The vector 3 struct.
     *
     * @tparam T - which number type.
     */
    template <typename T>
    struct Vec3
    {
        T X;
        T Y;
        T Z;

        /**
         * @brief Construct a new Vec 3 object
         * The default empty constructor.
         */
        Vec3()
        {
            X = 0;
            Y = 0;
            Z = 0;
        }

        /**
         * @brief Construct a new Vec 3 object.
         *
         * @param x - x component.
         * @param y - y component.
         * @param z - z component.
         */
        Vec3(T x, T y, T z)
            : X(x), Y(y), Z(z)
        {
        }

        /**
         * @brief The subtraction operator.
         *
         * @param a - vector to subtract.
         * @return Vec3<T>
         */
        Vec3<T> operator-(const Vec3<T> &a)
        {
            Vec3<T> r;
            r.X = X - a.X;
            r.Y = Y - a.Y;
            r.Z = Z - a.Z;
            return r;
        }

        /**
         * @brief Get the magnitude of a vector.
         *
         * @return T
         */
        T Magnitude() const
        {
            return std::sqrt(X * X + Y * Y + Z * Z);
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
            Z /= l;
        }

        /**
         * @brief The dot product with other vector.
         *
         * @param const Vec3<T>& other
         * @return T
         */
        T Dot(const Vec3<T> &other)
        {
            return X * other.X + Y * other.Y + Z * other.Z;
        }

        /**
         * @brief Returns new result as cross product between two vectors.
         *
         * @param const Vec3<T>& a
         * @param const Vec3<T>& b
         * @return Vec3<T>
         */
        static Vec3<T> Cross(const Vec3<T> &a, const Vec3<T> &b)
        {
            Vec3<T> r;
            r.X = a.Y * b.Z - b.Y * a.Z;
            r.Y = a.Z * b.X - b.Z * a.X;
            r.Z = a.X * b.Y - b.X * a.Y;
            return r;
        }

        /**
         * @brief The dot product between two vectors.
         *
         * @param const Vec3<T>& a
         * @param const Vec3<T>& b
         * @return Vec3<T>
         */
        static Vec3<T> Dot(const Vec3<T> &a, const Vec3<T> &b)
        {
            return a.X * b.X + a.Y + b.Y + a.Z + b.Z;
        }

        /**
         * @brief Returns the zero vector.
         *
         * @return Vec3<T>
         */
        static Vec3<T> Zero()
        {
            return Vec3(0, 0, 0);
        }

        /**
         * @brief Returns the vector with all components being set to 1.
         *
         * @return Vec3<T>
         */
        static Vec3<T> One()
        {
            return Vec3(1, 1, 1);
        }

        /**
         * @brief Returns the unit x vector.
         * @return Vec3<T>
         */
        static Vec3<T> UnitX()
        {
            return Vec3(1, 0, 0);
        }

        /// <summary>
        /// Returns the unit y vector.
        /// </summary>
        static Vec3<T> UnitY()
        {
            return Vec3(0., 1, 0);
        }

        /// <summary>
        /// Returns the unit z vector.
        /// </summary>
        /// <returns></returns>
        static Vec3<T> UnitZ()
        {
            return Vec3(0, 0, 1);
        }

        /// <summary>
        /// Returns the negative unit z vector.
        /// </summary>
        static Vec3<T> NegativeUnitZ()
        {
            return Vec3(0, 0, -1);
        }
    };

    template <typename T>
    Vec3<T> operator+(const Vec3<T> &a, const Vec3<T> &b)
    {
        Vec3<T> r;
        r.X = a.X + b.X;
        r.Y = a.Y + b.Y;
        r.Z = a.Z + b.Z;
        return r;
    }

    typedef Vec3<f32> Vec3f;
};

#endif