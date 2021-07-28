#pragma once
#ifndef REAL2X2_H
#define REAL2X2_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/integer.h"

#include "../numbers/real.h"
#include "../vectors/real2.h"
#include "../vectors/real3.h"
#include "../vectors/real4.h"

namespace geodesuka {
	namespace core {
		namespace math {

			union real2x2 {
				static const real2x2 I;

#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				struct {
					real xx, xy;
					real yx, yy;
				};
#endif

#ifdef COL_MAJOR_MEMORY_LAYOUT
				// Column Major Memory Layout
				struct {
					real xx, yx;
					real xy, yy;
				};
#endif
				//struct {
				//	real2 x;
				//	real2 y;
				//};
				//real2 vptr[2];
				real aptr[2][2];
				real ptr[2 * 2];


				real2x2() :
					xx(0.0), xy(0.0),
					yx(0.0), yy(0.0)
				{}
				real2x2(
					real XX, real XY,
					real YX, real YY
				) :
					xx(XX), xy(XY),
					yx(YX), yy(YY)
				{}
				~real2x2() {}

				// Access elements of matrix in standard notation.
				real operator()(integer RowElement, integer ColumnElement) const;
				real& operator()(integer RowElement, integer ColumnElement);

				real2x2 operator-() const;
				real2x2 operator+(const real2x2& Rhs) const;
				real2x2 operator-(const real2x2& Rhs) const;
				real2x2 operator*(const real2x2& Rhs) const;

				real2x2 operator+=(const real2x2& Rhs);
				real2x2 operator-=(const real2x2& Rhs);
				real2x2 operator*=(const real2x2& Rhs);

				real2 operator*(const real2& Rhs) const;
				real2x2 operator*(real Rhs) const;
				real2x2 operator/(real Rhs) const;

				//real sub(integer RowElement, integer ColumnElement) const;
				void setr(const real2& Row1, const real2& Row2);
				void setc(const real2& Col1, const real2& Col2);

			};

			real2 operator*(const real2& Lhs, const real2x2& Rhs);
			real2x2 operator*(real Lhs, const real2x2& Rhs);

			real det(const real2x2& Arg);
			real tr(const real2x2& Arg);
			real2x2 transpose(const real2x2& Arg);
			real2x2 inverse(const real2x2& Arg);

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real2x2& Arg);
#endif // MATH_ENABLE_IO

		}
	}
}

#endif // !REAL2X2_H

