#pragma once
#ifndef REAL3X4_H
#define REAL3X4_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/real.h"
#include "../vectors/real2.h"
#include "../vectors/real3.h"
#include "../vectors/real4.h"

namespace geodesuka {
	namespace core {
		namespace math {

			union real3x4 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				struct {
					real xx, xy, xz, xt;
					real yx, yy, yz, yt;
					real zx, zy, zz, zt;
				};
				//struct {
				//	real4 x, y, z;
				//};
				//real4 vptr[3];
				real aptr[3][4];
#else
				// Column Major Memory Layout
				struct {
					real xx, yx, zx;
					real xy, yy, zy;
					real xz, yz, zz;
					real xt, yt, zt;
				};
				//struct {
				//	real3 x, y, z, t;
				//};
				//real3 vptr[4];
				real aptr[4][3];
#endif // !COL_MAJOR_MEMORY_LAYOUT
				real ptr[3 * 4];

				real3x4() :
					xx(0.0), xy(0.0), xz(0.0), xt(0.0),
					yx(0.0), yy(0.0), yz(0.0), yt(0.0),
					zx(0.0), zy(0.0), zz(0.0), zt(0.0)
				{}
				real3x4(
					real XX, real XY, real XZ, real XT,
					real YX, real YY, real YZ, real YT,
					real ZX, real ZY, real ZZ, real ZT
				) :
					xx(XX), xy(XY), xz(XZ), xt(XT),
					yx(YX), yy(YY), yz(YZ), yt(YT),
					zx(ZX), zy(ZY), zz(ZZ), zt(ZT)
				{}
				~real3x4() {}

				// Access elements of matrix in standard notation.
				real operator()(integer RowElement, integer ColumnElement) const;
				real& operator()(integer RowElement, integer ColumnElement);

				// Basic Addition and Subtraction
				real3x4 operator-() const;
				real3x4 operator+(const real3x4& Rhs) const;
				real3x4 operator-(const real3x4& Rhs) const;

				real3x4& operator+=(const real3x4& Rhs);
				real3x4& operator-=(const real3x4& Rhs);

				// Multiply column vector
				real3 operator*(const real4& Rhs) const;

				// Scalar Multiplication
				real3x4 operator*(real Rhs) const;
				real3x4 operator/(real Rhs) const;

				// Set Rows/Columns using respective vectors
				void setr(const real4& Row1, const real4& Row2, const real4& Row3);
				void setc(const real3& Col1, const real3& Col2, const real3& Col3, const real3& Col4);

			};

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real3x4& Arg);
#endif // MATH_ENABLE_IO

		}
	}
}

#endif // !REAL3X4_H
