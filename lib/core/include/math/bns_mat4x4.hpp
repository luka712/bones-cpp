#ifndef BNS_MATH_MAT4x4_HPP

#define BNS_MATH_MAT4x4_HPP

#include <cmath>
#include "bns_types.hpp"
#include "math/bns_vec3.hpp"
#include "math/bns_mat3x3.hpp"

namespace bns
{

	template <typename T>
	struct Mat4x4
	{
		T R0C0;
		T R1C0;
		T R2C0;
		T R3C0;

		T R0C1;
		T R1C1;
		T R2C1;
		T R3C1;

		T R0C2;
		T R1C2;
		T R2C2;
		T R3C2;

		T R0C3;
		T R1C3;
		T R2C3;
		T R3C3;

		/// @brief Construct a new Mat 4x 4 object
		/// @param T r0c0
		/// @param T r0c1
		/// @param T r0c2
		/// @param T r0c3
		/// @param T r1c0
		/// @param T r1c1
		/// @param T r1c2
		/// @param T r1c3
		/// @param T r2c0
		/// @param T r2c1
		/// @param T r2c2
		/// @param T r2c3
		/// @param T r3c0
		/// @param T r3c1
		/// @param T r3c2
		/// @param T r3c3
		Mat4x4(
			T r0c0, T r0c1, T r0c2, T r0c3,
			T r1c0, T r1c1, T r1c2, T r1c3,
			T r2c0, T r2c1, T r2c2, T r2c3,
			T r3c0, T r3c1, T r3c2, T r3c3)
		{
			R0C0 = r0c0;
			R1C0 = r1c0;
			R2C0 = r2c0;
			R3C0 = r3c0;

			R0C1 = r0c1;
			R1C1 = r1c1;
			R2C1 = r2c1;
			R3C1 = r3c1;

			R0C2 = r0c2;
			R1C2 = r1c2;
			R2C2 = r2c2;
			R3C2 = r3c2;

			R0C3 = r0c3;
			R1C3 = r1c3;
			R2C3 = r2c3;
			R3C3 = r3c3;
		}

		/**
		 * @brief Construct a new Mat 4x4 as identity matrix.
		 *
		 */
		Mat4x4()
			: Mat4x4(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1)
		{
		}

		/// <summary>
		/// Returns identity matrix.
		/// </summary>
		/// <returns>The identity matrix</returns>
		static Mat4x4<T> Identity()
		{
			return Mat4x4<T>();
		}

		/**
		 * @brief Create the scale matrix.
		 *
		 * @param const Vec3<T>& scale_vector
		 * @return Mat4x4<T>
		 */
		Mat4x4<T> ScaleMatrix(const Vec3<T>& scale_vector)
		{
			Mat4x4<f32> r;
			r.R0C0 = scale_vector.X;
			r.R1C1 = scale_vector.Y;
			r.R2C2 = scale_vector.Z;
			return r;
		}

		/**
		 * @brief Create the scale matrix.
		 *
		 * @param T x
		 * @param T y
		 * @param T z
		 * @return Mat4x4<T>
		 */
		static Mat4x4<T> ScaleMatrix(T x, T y, T z)
		{
			Mat4x4<T> r;
			r.R0C0 = x;
			r.R1C1 = y;
			r.R2C2 = z;
			return r;
		}

		/**
		 * @brief Create a translation matrix.
		 *
		 * @param T x - translation in x axis.
		 * @param T y - translation in y axis.
		 * @param T z - translation in z axis.
		 * @return Mat4x4<T>
		 */
		static Mat4x4<T> TranslationMatrix(T x, T y, T z)
		{
			Mat4x4<T> r;
			r.R0C3 = x;
			r.R1C3 = y;
			r.R2C3 = z;
			return r;
		}

		static Mat4x4<T> RotationMatrix(T theta_in_radians, Vec3<T> axis)
		{

			// I3 = identity 3x3 matrix
			//											  | xx xy xz |              | 0 -z y |
			// R(a, theta) = cos(theta)I3 + (1-cos(theta) | xy yy yz | + sin(theta) | z 0 -x |
			//											  | xz yz zz |              | -y x 0 |
			//					a		  +            b               +           c

			axis.Normalize();

			// Unit vector components. Unit vector is v/|v|  where v is vector, and |v| is length of vector.
			T x = axis.X;
			T y = axis.Y;
			T z = axis.Z;

			// roughly pi/2
			T cos_theta = std::cos(theta_in_radians);

			// same as cos(theta)I3
			Mat3x3<T> a(
				cos_theta, 0, 0,
				0, cos_theta, 0,
				0, 0, cos_theta);

			//   		    		 | xx xy xz |
			// same as (1-cos(theta) | xy yy yz |
			//						 | xz yz zz |
			T s = 1 - cos_theta;
			Mat3x3<T> b(
				x * x * s, x * y * s, x * z * s,
				x * y * s, y * y * s, y * z * s,
				x * z * s, y * z * s, z * z * s);

			//                    | 0 -z y |
			// same as sin(theta) | z 0 -x |
			//                    | -y x 0 |
			s = std::sin(theta_in_radians);
			Mat3x3<T> c(
				0.0, -z * s, y * s,
				z * s, 0.0, -x * s,
				-y * s, x * s, 0.0);

			// You will change this return call
			Mat3x3<T> sum = a + b + c;
			return Mat4x4::From(sum);
		}


		/// @brief Create a perspective projection matrix.
		/// @param fovRadians Field of view in radians.
		/// @param aspectRatio Aspect ratio of the screen.
		/// @param near Near clipping plane.
		/// @param far Far clipping plane.
		/// @return Mat4x4<T>
		/// @note Matrix is setup for left handed system with depth range of [0, 1].
		static Mat4x4<T> Perspective(T fovRadians, T aspectRatio, T near, T far)
		{
			T t = std::tan(fovRadians / 2.0);

			T r0c0 = 1.0 / (t * aspectRatio);
			T r1c1 = 1.0 / t;

			// normaly we have depth that's in range [0, 1]. But if we want 2 units depth [-1,1] we can override.
			T r2c2 = -far / (near - far); // scale 
			T r2c3 = (near * far) / (near - far); // translate

			return Mat4x4<T>(
				r0c0, 0.0, 0.0, 0.0,
				0.0, r1c1, 0.0, 0.0,
				0.0, 0.0, r2c2, r2c3,
				0.0, 0.0, 1.0, 0.0);
		}

		/// @brief Create ortographic projection matrix.
		/// It is assumed that the coordinate system is left handed and normalized device coordinates are in range x: [-1, 1], y: [-1, 1], z: [0, 1]
		/// @param T left
		/// @param T right
		/// @param T bottom
		/// @param T top
		/// @param T z_near
		/// @param T z_far
		/// @return Mat4x4<T>
		static Mat4x4<T> Orthographic(T left, T right, T bottom, T top, T z_near, T z_far)
		{
			// SCALE
			T r0c0 = 2 / (right - left);
			T r1c1 = 2 / (top - bottom);
			T r2c2 = 1 / (z_far - z_near);

			// TRANSLATE
			T r0c3 = -(right + left) / (right - left); // -1 to 1
			T r1c3 = -(top + bottom) / (top - bottom); // -1 to 1
			T r2c3 = -z_near / (z_far - z_near);	   // 0 to 1

			return Mat4x4<T>(
				r0c0, 0, 0, r0c3,
				0, r1c1, 0, r1c3,
				0, 0, r2c2, r2c3,
				0, 0, 0, 1);
		}

		/// @brief Create a look at matrix for left handed coordinate system.
		/// @param Vec3<T> eye
		/// @param Vec3<T> center
		/// @param Vec3<T> up
		/// @return Mat4x4<T>
		static Mat4x4<T> LookAt(Vec3<T> eye, Vec3<T> center, Vec3<T> up)
		{
			// Find forward vector or unitz vector.
			Vec3<T> forward = center - eye;
			forward.Normalize();

			// Use orthogonalization to find right and up vectors.
			Vec3<T> right = Vec3<T>::Cross(up, forward);
			right.Normalize();

			up = Vec3<T>::Cross(forward, right);
			up.Normalize();

			// right, up and forward make for a rotation matrix which should be translated.
			// eye should be in inverse translation part of the matrix.
			// Those two should be multiplied to get the final matrix.
			// We embed operation as follows.

			return Mat4x4<T>(
				right.X, right.Y, right.Z, -eye.Dot(right),
				up.X, up.Y, up.Z, -eye.Dot(up),
				forward.X, forward.Y, forward.Z, -eye.Dot(forward),
				0, 0, 0, 1);

		}

		/**
		 * @brief Create matrix 4 from matrix 3.
		 *
		 * @param matrix - the 3x3 matrix.
		 * @return new matrix 4x4.
		 */
		static Mat4x4<T> From(Mat3x3<T> matrix)
		{
			return Mat4x4<T>(
				matrix.R0C0, matrix.R0C1, matrix.R0C2, 0,
				matrix.R1C0, matrix.R1C1, matrix.R1C2, 0,
				matrix.R2C0, matrix.R2C1, matrix.R2C2, 0,
				0, 0, 0, 1);
		}

		/// @brief Transpose the matrix.
		/// @return Transposed matrix.
		static Mat4x4<T> Transpose(Mat4x4<T>& other)
		{
			return Mat4x4<T>(
				other.R0C0, other.R1C0, other.R2C0, other.R3C0,
				other.R0C1, other.R1C1, other.R2C1, other.R3C1,
				other.R0C2, other.R1C2, other.R2C2, other.R3C2,
				other.R0C3, other.R1C3, other.R2C3, other.R3C3);
		}
	};

	template <typename T>
	Mat4x4<T> operator*(const Mat4x4<T>& a, const Mat4x4<T>& b)
	{
		Mat4x4<T> r(
			a.R0C0 * b.R0C0 + a.R0C1 * b.R1C0 + a.R0C2 * b.R2C0 + a.R0C3 * b.R3C0,
			a.R0C0 * b.R0C1 + a.R0C1 * b.R1C1 + a.R0C2 * b.R2C1 + a.R0C3 * b.R3C1,
			a.R0C0 * b.R0C2 + a.R0C1 * b.R1C2 + a.R0C2 * b.R2C2 + a.R0C3 * b.R3C2,
			a.R0C0 * b.R0C3 + a.R0C1 * b.R1C3 + a.R0C2 * b.R2C3 + a.R0C3 * b.R3C3,

			a.R1C0 * b.R0C0 + a.R1C1 * b.R1C0 + a.R1C2 * b.R2C0 + a.R1C3 * b.R3C0,
			a.R1C0 * b.R0C1 + a.R1C1 * b.R1C1 + a.R1C2 * b.R2C1 + a.R1C3 * b.R3C1,
			a.R1C0 * b.R0C2 + a.R1C1 * b.R1C2 + a.R1C2 * b.R2C2 + a.R1C3 * b.R3C2,
			a.R1C0 * b.R0C3 + a.R1C1 * b.R1C3 + a.R1C2 * b.R2C3 + a.R1C3 * b.R3C3,

			a.R2C0 * b.R0C0 + a.R2C1 * b.R1C0 + a.R2C2 * b.R2C0 + a.R2C3 * b.R3C0,
			a.R2C0 * b.R0C1 + a.R2C1 * b.R1C1 + a.R2C2 * b.R2C1 + a.R2C3 * b.R3C1,
			a.R2C0 * b.R0C2 + a.R2C1 * b.R1C2 + a.R2C2 * b.R2C2 + a.R2C3 * b.R3C2,
			a.R2C0 * b.R0C3 + a.R2C1 * b.R1C3 + a.R2C2 * b.R2C3 + a.R2C3 * b.R3C3,

			a.R3C0 * b.R0C0 + a.R3C1 * b.R1C0 + a.R3C2 * b.R2C0 + a.R3C3 * b.R3C0,
			a.R3C0 * b.R0C1 + a.R3C1 * b.R1C1 + a.R3C2 * b.R2C1 + a.R3C3 * b.R3C1,
			a.R3C0 * b.R0C2 + a.R3C1 * b.R1C2 + a.R3C2 * b.R2C2 + a.R3C3 * b.R3C2,
			a.R3C0 * b.R0C3 + a.R3C1 * b.R1C3 + a.R3C2 * b.R2C3 + a.R3C3 * b.R3C3);
		return r;
	}

	typedef Mat4x4<f32> Mat4x4f;
}

#endif
