#pragma once
#ifndef REAL3X3_H
#define REAL3X3_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/integer.h"
#include "../vectors/integer2.h"

#include "../numbers/real.h"
#include "../vectors/real2.h"
#include "../vectors/real3.h"
#include "../vectors/real4.h"

#include "real2x2.h"

namespace geodesuka {
	namespace core {
		namespace math {

			union real3x3 {
				static const real3x3 I;
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				struct {
					real xx, xy, xz;
					real yx, yy, yz;
					real zx, zy, zz;
				};
#else
				// Column Major Memory Layout
				struct {
					real xx, yx, zx;
					real xy, yy, zy;
					real xz, yz, zz;
				};
#endif // !COL_MAJOR_MEMORY_LAYOUT
				//struct {
				//	real3 x, y, z;
				//};
				//real3 vptr[3];
				real aptr[3][3];
				real ptr[3 * 3];

				real3x3() :
					xx(0.0), xy(0.0), xz(0.0),
					yx(0.0), yy(0.0), yz(0.0),
					zx(0.0), zy(0.0), zz(0.0)
				{}
				real3x3(
					real XX, real XY, real XZ,
					real YX, real YY, real YZ,
					real ZX, real ZY, real ZZ
				) :
					xx(XX), xy(XY), xz(XZ),
					yx(YX), yy(YY), yz(YZ),
					zx(ZX), zy(ZY), zz(ZZ)
				{}
				real3x3(const real3& Col1, const real3& Col2, const real3& Col3);
				real3x3(const real3x3& Arg);
				~real3x3() {}

				real3x3& operator=(const real3x3& Rhs);

				// Access elements of matrix in standard notation.
				real operator()(integer RowElement, integer ColumnElement) const;
				real& operator()(integer RowElement, integer ColumnElement);

				//real operator[](integer2 Index) const;
				//real& operator[](integer2 Index);

				real3x3 operator-() const;
				real3x3 operator+(const real3x3& Rhs) const;
				real3x3 operator-(const real3x3& Rhs) const;
				real3x3 operator*(const real3x3& Rhs) const;

				real3x3& operator+=(const real3x3& Rhs);
				real3x3& operator-=(const real3x3& Rhs);
				real3x3& operator*=(const real3x3& Rhs);

				real3 operator*(const real3& Rhs) const;
				real3x3 operator*(real Rhs) const;
				real3x3 operator/(real Rhs) const;

				real2x2 sub(integer RowElement, integer ColumnElement) const;
				void setr(const real3& Row1, const real3& Row2, const real3& Row3);
				void setc(const real3& Col1, const real3& Col2, const real3& Col3);

				friend real3 operator*(const real3& Lhs, const real3x3& Rhs);
				friend real3x3 operator*(real Lhs, const real3x3& Rhs);

			};

			real det(const real3x3& Arg);
			real tr(const real3x3& Arg);
			real3x3 transpose(const real3x3& Arg);
			real3x3 inverse(const real3x3& Arg);

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real3x3& Arg);
#endif // MATH_ENABLE_IO

		}
	}
}

#endif // !REAL3X3_H
