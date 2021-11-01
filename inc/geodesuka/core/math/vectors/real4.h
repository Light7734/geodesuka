#pragma once
#ifndef GEODESUKA_CORE_MATH_REAL4_H
#define GEODESUKA_CORE_MATH_REAL4_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO


#include "../numbers/natural.h"
#include "../numbers/integer.h"
#include "../numbers/real.h"

namespace geodesuka::core::math {

	union real4 {
		struct {
			real x, y, z, t;
		};
		struct {
			real r, g, b, a;
		};
		real ptr[4];

		real4();
		~real4();

#ifdef CS_PLEB_NOTATION
		real4(real Val);
#endif // CS_PLEB_NOTATION
		real4(real ValX, real ValY, real ValZ, real ValT);
		real4(const real4& Val);

#ifdef CS_PLEB_NOTATION
		real4& operator=(real Rhs);
#endif // CS_PLEB_NOTATION
		real4& operator=(const real4& Rhs);

		real operator[](integer Index) const;
		real& operator[](integer Index);

		real4 operator-() const;
		real4 operator+(const real4& Rhs) const;
		real4 operator-(const real4& Rhs) const;
		real operator*(const real4& Rhs) const;

		real4& operator+=(const real4& Rhs);
		real4& operator-=(const real4& Rhs);

#ifdef CS_PLEB_NOTATION
		real4 operator+(real Rhs) const;
		real4 operator-(real Rhs) const;
#endif // CS_PLEB_NOTATION
		real4 operator*(real Rhs) const;
		real4 operator/(real Rhs) const;

#ifdef CS_PLEB_NOTATION
		real4& operator+=(real Rhs);
		real4& operator-=(real Rhs);
#endif // CS_PLEB_NOTATION
		real4& operator*=(real Rhs);
		real4& operator/=(real Rhs);

	};

#ifdef CS_PLEB_NOTATION
	real4 operator+(real Lhs, const real4& Rhs);
	real4 operator-(real Lhs, const real4& Rhs);
#endif // CS_PLEB_NOTATION
	real4 operator*(real Lhs, const real4& Rhs);
#ifdef CS_PLEB_NOTATION
	real4 operator/(real Lhs, const real4& Rhs);
#endif // CS_PLEB_NOTATION

	real length(const real4& Arg);
	real4 normalize(const real4& Arg);

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& os, const real4& v);
#endif // MATH_ENABLE_IO

}

#endif // !GEODESUKA_CORE_MATH_REAL4_H
