#pragma once
#ifndef GEODESUKA_CORE_MATH_QUATERNION_H
#define GEODESUKA_CORE_MATH_QUATERNION_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/integer.h"
#include "../numbers/natural.h"
#include "../numbers/real.h"
#include "../numbers/complex.h"

namespace geodesuka::core::math {

	union quaternion {
		// Unit Versors
		static const quaternion i;
		static const quaternion j;
		static const quaternion k;

		struct {
			real b, c, d, a;
		};
		struct {
			real x, y, z, t;
		};
		real ptr[4];

		quaternion();
		~quaternion();

		quaternion(real Val);
		quaternion(real VReal, real VImag);
		quaternion(const complex& Val);
		quaternion(real ValA, real ValB, real ValC, real ValD);
		quaternion(const quaternion& Val);

		quaternion& operator=(real Rhs);
		quaternion& operator=(const complex& Rhs);
		quaternion& operator=(const quaternion& Rhs);

		real& operator[](integer Index);

		quaternion operator-() const;
		quaternion operator~() const;

		quaternion operator+(const quaternion& Rhs) const;
		quaternion operator-(const quaternion& Rhs) const;
		quaternion operator*(const quaternion& Rhs) const;
		quaternion operator/(const quaternion& Rhs) const;

		quaternion& operator+=(const quaternion& Rhs);
		quaternion& operator-=(const quaternion& Rhs);
		quaternion& operator*=(const quaternion& Rhs);
		quaternion& operator/=(const quaternion& Rhs);

		quaternion operator+(const complex& Rhs) const;
		quaternion operator-(const complex& Rhs) const;
		quaternion operator*(const complex& Rhs) const;
		quaternion operator/(const complex& Rhs) const;

		quaternion& operator+=(const complex& Rhs);
		quaternion& operator-=(const complex& Rhs);
		quaternion& operator*=(const complex& Rhs);
		quaternion& operator/=(const complex& Rhs);

		quaternion operator+(real Rhs) const;
		quaternion operator-(real Rhs) const;
		quaternion operator*(real Rhs) const;
		quaternion operator/(real Rhs) const;

		quaternion& operator+=(real Rhs);
		quaternion& operator-=(real Rhs);
		quaternion& operator*=(real Rhs);
		quaternion& operator/=(real Rhs);

	};

	quaternion operator+(const complex& Lhs, const quaternion& Rhs);
	quaternion operator-(const complex& Lhs, const quaternion& Rhs);
	quaternion operator*(const complex& Lhs, const quaternion& Rhs);
	quaternion operator/(const complex& Lhs, const quaternion& Rhs);

	quaternion operator+(real Lhs, const quaternion& Rhs);
	quaternion operator-(real Lhs, const quaternion& Rhs);
	quaternion operator*(real Lhs, const quaternion& Rhs);
	quaternion operator/(real Lhs, const quaternion& Rhs);

	real abs2(const quaternion& Arg);
	real abs(const quaternion& Arg);

	quaternion exp(const quaternion& Arg);
	quaternion ln(const quaternion& Arg);

	quaternion pow(const quaternion& Base, const quaternion& Exponent);

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& os, const quaternion& q);
#endif // MATH_ENABLE_IO

}

#endif // !GEODESUKA_CORE_MATH_QUATERNION_H
