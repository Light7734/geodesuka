#pragma once
#ifndef GEODESUKA_CORE_MATH_REAL2X3_H
#define GEODESUKA_CORE_MATH_REAL2X3_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/real.h"
#include "../vectors/real2.h"
#include "../vectors/real3.h"
#include "../vectors/real4.h"

//real A[3][2] = { {0,1}, {2,3}, {4,5} };
//real A[2][3] = { {0,1,2}, {3,4,5} };

namespace geodesuka::core::math {

	union real2x3 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
		// Row Major Memory Layout
		struct {
			real xx, xy, xz;
			real yx, yy, yz;
		};
		// Row Vectors
		//struct {
		//	real3 x;
		//	real3 y;
		//};
		//real3 vptr[2];
		real aptr[2][3];
#endif
#ifdef COL_MAJOR_MEMORY_LAYOUT
		// Column Major Memory Layout
		struct {
			real xx, yx;
			real xy, yy;
			real xz, yz;
		};
		// Column Vectors
		//struct {
		//	real2 x, y, z;
		//};
		//real2 vptr[3];
		real aptr[3][2];
#endif
		real ptr[2 * 3];

		real2x3() :
			xx(0.0), xy(0.0), xz(0.0),
			yx(0.0), yy(0.0), yz(0.0)
		{}
		real2x3(
			real XX, real XY, real XZ,
			real YX, real YY, real YZ
		) :
			xx(XX), xy(XY), xz(XZ),
			yx(YX), yy(YY), yz(YZ)
		{}
		//real2x3(const real2& Col1, const real2& Col2, const real2& Col3) :
		//	xx(Col1.x), xy(Col2.x), xz(Col3.x),
		//	yx(Col1.y), yy(Col2.y), yz(Col3.y)
		//{}
		real2x3(const real2x3& Arg);
		~real2x3() {}

		real2x3& operator=(const real2x3& Rhs);

		real operator()(integer RowElement, integer ColumnElement) const;
		real& operator()(integer RowElement, integer ColumnElement);

		// Basic Addition and Subtraction
		real2x3 operator-() const;
		real2x3 operator+(const real2x3& Rhs) const;
		real2x3 operator-(const real2x3& Rhs) const;

		real2x3& operator+=(const real2x3& Rhs);
		real2x3& operator-=(const real2x3& Rhs);

		// Multiply column vector
		real2 operator*(const real3& Rhs) const;

		// Scalar Multiplication/Division
		real2x3 operator*(real Rhs) const;
		real2x3 operator/(real Rhs) const;

		void setr(const real3& Row1, const real3& Row2);
		void setc(const real2& Col1, const real2& Col2, const real2& Col3);

	};

	real3 operator*(const real2& Lhs, const real2x3& Rhs);
	real2x3 operator*(real Lhs, const real2x3& Rhs);

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& Out, const real2x3& Arg);
#endif // MATH_ENABLE_IO

}

#endif // !GEODESUKA_CORE_MATH_REAL2X3_H
