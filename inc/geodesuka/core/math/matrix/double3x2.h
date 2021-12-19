#pragma once
#ifndef GEODESUKA_CORE_MATH_REAL3X2_H
#define GEODESUKA_CORE_MATH_REAL3X2_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/real.h"
#include "../vectors/real2.h"
#include "../vectors/real3.h"
#include "../vectors/real4.h"

namespace geodesuka::core::math {

	//struct real3x2 {
	//	real a11, a21;
	//	real a12, a22;
	//	real a13, a23;
	//};

	union real3x2 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
		// Row Major Memory Layout
		struct {
			real xx, xy;
			real yx, yy;
			real zx, zy;
		};
		// Row Vectors
		//struct {
		//	real2 x;
		//	real2 y;
		//	real2 z;
		//};
		//real3 vptr[2];
		real aptr[3][2];
#else
		// Column Major Memory Layout
		struct {
			real xx, yx, zx;
			real xy, yy, zy;
		};
		// Column Vectors
		//struct {
		//	real3 x, y;
		//};
		//real2 vptr[3];
		real aptr[3][2];
#endif // !COL_MAJOR_MEMORY_LAYOUT
		real ptr[2 * 3];

		real3x2() :
			xx(0.0), xy(0.0),
			yx(0.0), yy(0.0),
			zx(0.0), zy(0.0)
		{}
		real3x2(
			real XX, real XY,
			real YX, real YY,
			real ZX, real ZY
		) :
			xx(XX), xy(XY),
			yx(YX), yy(YY),
			zx(ZX), zy(ZY)
		{}
		~real3x2() {}

		// Access elements of matrix in standard notation.
		real operator()(integer RowElement, integer ColumnElement) const;
		real& operator()(integer RowElement, integer ColumnElement);

		// Basic Addition and Subtraction
		real3x2 operator-() const;
		real3x2 operator+(const real3x2& Rhs) const;
		real3x2 operator-(const real3x2& Rhs) const;

		real3x2& operator+=(const real3x2& Rhs);
		real3x2& operator-=(const real3x2& Rhs);

		// Multiply column vector
		real3 operator*(const real2& Rhs) const;

		// Scalar Multiplication
		real3x2 operator*(real Rhs) const;
		real3x2 operator/(real Rhs) const;

		void setr(const real2& Row1, const real2& Row2, const real2& Row3);
		void setc(const real3& Col1, const real3& Col2);

	};

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& Out, const real3x2& Arg);
#endif // MATH_ENABLE_IO

}

#endif // !GEODESUKA_CORE_MATH_REAL3X2_H

