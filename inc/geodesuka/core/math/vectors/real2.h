#pragma once
#ifndef REAL2_H
#define REAL2_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO


#include "../numbers/natural.h"
#include "../numbers/integer.h"
#include "../numbers/real.h"

namespace geodesuka {
	namespace core {
		namespace math {

			union real2 {
				struct {
					real x, y;
				};
				struct {
					real a, b;
				};
				real ptr[2];

				real2();
				~real2();

#ifdef CS_PLEB_NOTATION
				real2(real Val); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
				real2(real ValX, real ValY);
				real2(const real2& Val);

#ifdef CS_PLEB_NOTATION
				real2& operator=(real Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
				real2& operator=(const real2& Rhs);

				real operator[](integer Index) const;
				real& operator[](integer Index);

				real2 operator-() const;
				real2 operator+(const real2& Rhs) const;
				real2 operator-(const real2& Rhs) const;
				real operator*(const real2& Rhs) const;
				real operator^(const real2& Rhs) const;

				real2& operator+=(const real2& Rhs);
				real2& operator-=(const real2& Rhs);

#ifdef CS_PLEB_NOTATION
				real2 operator+(real Rhs) const; /* Technically not legal, but useful */
				real2 operator-(real Rhs) const; /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
				real2 operator*(real Rhs) const;
				real2 operator/(real Rhs) const;

#ifdef CS_PLEB_NOTATION
				real2& operator+=(real Rhs); /* Technically not legal, but useful */
				real2& operator-=(real Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
				real2& operator*=(real Rhs);
				real2& operator/=(real Rhs);

			};

#ifdef CS_PLEB_NOTATION
			real2 operator+(real Lhs, const real2& Rhs); /* Technically not legal, but useful */
			real2 operator-(real Lhs, const real2& Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
			real2 operator*(real Lhs, const real2& Rhs);
#ifdef CS_PLEB_NOTATION
			real2 operator/(real Lhs, const real2& Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION

			real length(const real2& Arg);
			real2 normalize(const real2& Arg);

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& os, const real2& v);
#endif // MATH_ENABLE_IO

		}
	}
}

#endif // !REAL2_H
