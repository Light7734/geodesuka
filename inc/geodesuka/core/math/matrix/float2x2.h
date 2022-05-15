#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT2X2_H
#define GEODESUKA_CORE_MATH_FLOAT2X2_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../number/type.h"
#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"

	union float2x2 {
		static const float2x2 I;

#ifdef ROW_MAJOR_MEMORY_LAYOUT
		// Row Major Memory Layout
		struct {
			float xx, xy;
			float yx, yy;
		};
#endif

#ifdef COL_MAJOR_MEMORY_LAYOUT
		// Column Major Memory Layout
		struct {
			float xx, yx;
			float xy, yy;
		};
#endif
		//struct {
		//	float2 x;
		//	float2 y;
		//};
		//float2 vptr[2];
		float aptr[2][2];
		float ptr[2 * 2];


		float2x2() :
			xx(0.0), xy(0.0),
			yx(0.0), yy(0.0)
		{}
		float2x2(
			float XX, float XY,
			float YX, float YY
		) :
			xx(XX), xy(XY),
			yx(YX), yy(YY)
		{}
		~float2x2() {}

		// Access elements of matrix in standard notation.
		float operator()(int RowElement, int ColumnElement) const;
		float& operator()(int RowElement, int ColumnElement);

		float2x2 operator-() const;
		float2x2 operator+(const float2x2& Rhs) const;
		float2x2 operator-(const float2x2& Rhs) const;
		float2x2 operator*(const float2x2& Rhs) const;

		float2x2 operator+=(const float2x2& Rhs);
		float2x2 operator-=(const float2x2& Rhs);
		float2x2 operator*=(const float2x2& Rhs);

		float2 operator*(const float2& Rhs) const;
		float2x2 operator*(float Rhs) const;
		float2x2 operator/(float Rhs) const;

		//float sub(integer RowElement, integer ColumnElement) const;
		void setr(const float2& Row1, const float2& Row2);
		void setc(const float2& Col1, const float2& Col2);

	};

	float2 operator*(const float2& Lhs, const float2x2& Rhs);
	float2x2 operator*(float Lhs, const float2x2& Rhs);

	float det(const float2x2& Arg);
	float tr(const float2x2& Arg);
	float2x2 transpose(const float2x2& Arg);
	float2x2 inverse(const float2x2& Arg);

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& Out, const float2x2& Arg);
#endif // MATH_ENABLE_IO


#endif // !GEODESUKA_CORE_MATH_FLOAT2X2_H

