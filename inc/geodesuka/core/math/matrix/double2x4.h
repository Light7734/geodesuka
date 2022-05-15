#pragma once
#ifndef GEODESUKA_CORE_MATH_REAL2X4_H
#define GEODESUKA_CORE_MATH_REAL2X4_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/real.h"
#include "../vectors/real2.h"
#include "../vectors/real3.h"
#include "../vectors/real4.h"

namespace geodesuka::core::math {

	//struct real2x4 {
	//	real a11, a21, a31, a41;
	//	real a12, a22, a32, a42;
	//};

	union real2x4 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
		// Row Major Memory Layout
		struct {
			real xx, xy, xz, xt;
			real yx, yy, yz, yt;
		};
		// Row Vectors
		//struct {
		//	real4 x;
		//	real4 y;
		//};
		//real3 vptr[2];
		real aptr[2][4];
#else
		// Column Major Memory Layout
		struct {
			real xx, yx;
			real xy, yy;
			real xz, yz;
			real xt, yt;
		};
		// Column Vectors
		//struct {
		//	real2 x, y, z, t;
		//};
		//real2 vptr[4];
		real aptr[4][2];
#endif // !COL_MAJOR_MEMORY_LAYOUT
		real ptr[2 * 4];

		real2x4() :
			xx(0.0), xy(0.0), xz(0.0), xt(0.0),
			yx(0.0), yy(0.0), yz(0.0), yt(0.0)
		{}
		real2x4(
			real XX, real XY, real XZ, real XT,
			real YX, real YY, real YZ, real YT
		) :
			xx(XX), xy(XY), xz(XZ), xt(XT),
			yx(YX), yy(YY), yz(YZ), yt(YT)
		{}
		~real2x4() {}

		// Access elements of matrix in standard notation.
		real operator()(integer RowElement, integer ColumnElement) const;
		real& operator()(integer RowElement, integer ColumnElement);

		// Basic Addition and Subtraction
		real2x4 operator-() const;
		real2x4 operator+(const real2x4& Rhs) const;
		real2x4 operator-(const real2x4& Rhs) const;

		real2x4& operator+=(const real2x4& Rhs);
		real2x4& operator-=(const real2x4& Rhs);

		// Multiply column vector
		real2 operator*(const real4& Rhs) const;

		// Scalar Multiplication
		real2x4 operator*(real Rhs) const;
		real2x4 operator/(real Rhs) const;

		void setr(const real4& Row1, const real4& Row2);
		void setc(const real2& Col1, const real2& Col2, const real2& Col3, const real2& Col4);

	};

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& Out, const real2x4& Arg);
#endif // MATH_ENABLE_IO

}

#endif // !GEODESUKA_CORE_MATH_REAL2X4_H

