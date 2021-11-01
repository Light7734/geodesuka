#pragma once
#ifndef GEODESUKA_CORE_MATH_REAL4X3_H
#define GEODESUKA_CORE_MATH_REAL4X3_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/real.h"
#include "../vectors/real2.h"
#include "../vectors/real3.h"
#include "../vectors/real4.h"

namespace geodesuka::core::math {

	//struct real4x3 {
	//	real xx, yx, zx;
	//	real xy, yy, zy;
	//	real xz, yz, zz;
	//	real xt, yt, zt;
	//};

	union real4x3 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
		// Row Major Memory Layout
		struct {
			real xx, xy, xz;
			real yx, yy, yz;
			real zx, zy, zz;
			real tx, ty, tz;
		};
		// Row vectors
		//struct {
		//	real3 x, y, z, t;
		//};
		//real3 vptr[4];
		real aptr[4][3];
#else
		// Column Major Memory Layout
		struct {
			real xx, yx, zx, tx;
			real xy, yy, zy, ty;
			real xz, yz, zz, tz;
		};
		// Column Vectors
		//struct {
		//	real4 x, y, z;
		//};
		//real4 vptr[3];
		real aptr[3][4];
#endif // !COL_MAJOR_MEMORY_LAYOUT
		real ptr[4 * 3];

		real4x3() :
			xx(0.0), xy(0.0), xz(0.0),
			yx(0.0), yy(0.0), yz(0.0),
			zx(0.0), zy(0.0), zz(0.0),
			tx(0.0), ty(0.0), tz(0.0)
		{}
		real4x3(
			real XX, real XY, real XZ,
			real YX, real YY, real YZ,
			real ZX, real ZY, real ZZ,
			real TX, real TY, real TZ
		) :
			xx(XX), xy(XY), xz(XZ),
			yx(YX), yy(YY), yz(YZ),
			zx(ZX), zy(ZY), zz(ZZ),
			tx(TX), ty(TY), tz(TZ)
		{}
		~real4x3() {}

		// Access elements of matrix in standard notation.
		real operator()(integer RowElement, integer ColumnElement) const;
		real& operator()(integer RowElement, integer ColumnElement);

		// Basic Addition and Subtraction
		real4x3 operator-() const;
		real4x3 operator+(const real4x3& Rhs) const;
		real4x3 operator-(const real4x3& Rhs) const;

		real4x3& operator+=(const real4x3& Rhs);
		real4x3& operator-=(const real4x3& Rhs);

		// Multiply column vector
		real4 operator*(const real3& Rhs) const;

		// Scalar Multiplication
		real4x3 operator*(real Rhs) const;
		real4x3 operator/(real Rhs) const;

		// Set Rows/Columns using respective vectors
		void setr(const real3& Row1, const real3& Row2, const real3& Row3, const real3& Row4);
		void setc(const real4& Col1, const real4& Col2, const real4& Col3);

	};

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& Out, const real4x3& Arg);
#endif // MATH_ENABLE_IO

}

#endif // !GEODESUKA_CORE_MATH_REAL4X3_H

