#ifndef BNS_MATH_MAT3x3_H

#define BNS_MATH_MAT3x3_H

#include <cmath>
#include "bns_types.hpp"

namespace bns
{

	template <typename T>
	struct Mat3x3
	{
		T R0C0;
		T R1C0;
		T R2C0;

		T R0C1;
		T R1C1;
		T R2C1;

		T R0C2;
		T R1C2;
		T R2C2;

		/**
		 * @brief Construct a new Mat3x3.
		 *
		 * @param T r0c0
		 * @param T r0c1
		 * @param T r0c2
		 * @param T r1c0
		 * @param T r1c1
		 * @param T r1c2
		 * @param T r2c0
		 * @param T r2c1
		 * @param T r2c2
		 */
		Mat3x3(
			T r0c0, T r0c1, T r0c2,
			T r1c0, T r1c1, T r1c2,
			T r2c0, T r2c1, T r2c2)
		{
			R0C0 = r0c0;
			R1C0 = r1c0;
			R2C0 = r2c0;

			R0C1 = r0c1;
			R1C1 = r1c1;
			R2C1 = r2c1;

			R0C2 = r0c2;
			R1C2 = r1c2;
			R2C2 = r2c2;
		}

		/**
		 * @brief Construct a new Mat3x3 as identity matrix.
		 *
		 */
		Mat3x3()
			: Mat3x3(1, 0, 0,
					 0, 1, 0,
					 0, 0, 1)
		{
		}
	};

	template <typename T>
	Mat3x3<T> operator+(const Mat3x3<T> &a, const Mat3x3<T> &b)
	{
		Mat3x3<T> r(
			a.R0C0 + b.R0C0, a.R0C1 + b.R0C1, a.R0C2 + b.R0C2,
			a.R1C0 + b.R1C0, a.R1C1 + b.R1C1, a.R1C2 + b.R1C2,
			a.R2C0 + b.R2C0, a.R2C1 + b.R2C1, a.R2C2 + b.R2C2);
		return r;
	}


    typedef Mat3x3<f32> Mat3x3f;
}

#endif