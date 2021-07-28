#pragma once
#ifndef REAL4X2_H
#define REAL4X2_H

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

			union real4x2 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				struct {
					real xx, xy;
					real yx, yy;
					real zx, zy;
					real tx, ty;
				};
				// Row vectors
				//struct {
				//	real2 x, y, z, t;
				//};
				//real2 vptr[4];
				real aptr[4][2];
#else
				// Column Major Memory Layout
				struct {
					real xx, yx, zx, tx;
					real xy, yy, zy, ty;
				};
				// Column Vectors
				//struct {
				//	real4 x, y;
				//};
				//real4 vptr[2];
				real aptr[2][4];
#endif // !COL_MAJOR_MEMORY_LAYOUT
				real ptr[4 * 2];

				real4x2() :
					xx(0.0), xy(0.0),
					yx(0.0), yy(0.0),
					zx(0.0), zy(0.0),
					tx(0.0), ty(0.0)
				{}
				real4x2(
					real XX, real XY,
					real YX, real YY,
					real ZX, real ZY,
					real TX, real TY
				) :
					xx(XX), xy(XY),
					yx(YX), yy(YY),
					zx(ZX), zy(ZY),
					tx(TX), ty(TY)
				{}
				~real4x2() {}

				// Access elements of matrix in standard notation.
				real operator()(integer RowElement, integer ColumnElement) const;
				real& operator()(integer RowElement, integer ColumnElement);

				// Basic Addition and Subtraction
				real4x2 operator-() const;
				real4x2 operator+(const real4x2& Rhs) const;
				real4x2 operator-(const real4x2& Rhs) const;

				real4x2& operator+=(const real4x2& Rhs);
				real4x2& operator-=(const real4x2& Rhs);

				// Multiply column vector
				real4 operator*(const real2& Rhs) const;

				// Scalar Multiplication
				real4x2 operator*(real Rhs) const;
				real4x2 operator/(real Rhs) const;

				// Set Rows/Columns using respective vectors
				void setr(const real2& Row1, const real2& Row2, const real2& Row3, const real2& Row4);
				void setc(const real4& Col1, const real4& Col2);

			};

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real4x2& Arg);
#endif // MATH_ENABLE_IO

		}
	}
}

#endif // !REAL4X2_H
