#pragma once
#ifndef GEODESUKA_CORE_MATH_REAL3_H
#define GEODESUKA_CORE_MATH_REAL3_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO


#include "../numbers/natural.h"
#include "../numbers/integer.h"
#include "../numbers/real.h"

namespace geodesuka::core::math {

	union real3 {
		struct {
			real x, y, z;
		};
		struct {
			real r, g, b;
		};
		real ptr[3];

		real3();
		~real3();

#ifdef CS_PLEB_NOTATION
		real3(real Val);
#endif // CS_PLEB_NOTATION
		real3(real ValX, real ValY, real ValZ);
		real3(const real3& Val);
		//real3(real3&& RR);

#ifdef CS_PLEB_NOTATION
		real3& operator=(real Rhs);
#endif // CS_PLEB_NOTATION
		//real3& operator=(real X, real Y, real Z);
		real3& operator=(const real3& Rhs);
		//real3& operator=(real3&& Rhs);

		real operator[](integer Index) const;
		real& operator[](integer Index);

		real3 operator-() const;
		real3 operator+(const real3& Rhs) const;
		real3 operator-(const real3& Rhs) const;
		real operator*(const real3& Rhs) const;
		real3 operator^(const real3& Rhs) const;

		real3& operator+=(const real3& Rhs);
		real3& operator-=(const real3& Rhs);
		real3& operator^=(const real3& Rhs);

#ifdef CS_PLEB_NOTATION
		real3 operator+(real Rhs) const; /* Technically not legal, but useful */
		real3 operator-(real Rhs) const; /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
		real3 operator*(real Rhs) const;
		real3 operator/(real Rhs) const;

#ifdef CS_PLEB_NOTATION
		real3& operator+=(real Rhs); /* Technically not legal, but useful */
		real3& operator-=(real Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
		real3& operator*=(real Rhs);
		real3& operator/=(real Rhs);

	};

#ifdef CS_PLEB_NOTATION
	real3 operator+(real Lhs, const real3& Rhs); /* Technically not legal, but useful */
	real3 operator-(real Lhs, const real3& Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
	real3 operator*(real Lhs, const real3& Rhs);
#ifdef CS_PLEB_NOTATION
	real3 operator/(real Lhs, const real3& Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION

	real length(const real3& Arg);
	real3 normalize(const real3& Arg);

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& os, const real3& v);
#endif // MATH_ENABLE_IO

}

#endif // !REAL3_H
