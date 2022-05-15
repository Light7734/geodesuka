#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT2X4_H
#define GEODESUKA_CORE_MATH_FLOAT2X4_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../number/type.h"

#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"

//struct float2x4 {
//	float a11, a21, a31, a41;
//	float a12, a22, a32, a42;
//};

union float2x4 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	struct {
		float xx, xy, xz, xt;
		float yx, yy, yz, yt;
	};
	// Row Vectors
	//struct {
	//	float4 x;
	//	float4 y;
	//};
	//float3 vptr[2];
	float aptr[2][4];
#else
	// Column Major Memory Layout
	struct {
		float xx, yx;
		float xy, yy;
		float xz, yz;
		float xt, yt;
	};
	// Column Vectors
	//struct {
	//	float2 x, y, z, t;
	//};
	//float2 vptr[4];
	float aptr[4][2];
#endif // !COL_MAJOR_MEMORY_LAYOUT
	float ptr[2 * 4];

	float2x4() :
		xx(0.0), xy(0.0), xz(0.0), xt(0.0),
		yx(0.0), yy(0.0), yz(0.0), yt(0.0)
	{}
	float2x4(
		float XX, float XY, float XZ, float XT,
		float YX, float YY, float YZ, float YT
	) :
		xx(XX), xy(XY), xz(XZ), xt(XT),
		yx(YX), yy(YY), yz(YZ), yt(YT)
	{}
	~float2x4() {}

	// Access elements of matrix in standard notation.
	float operator()(int RowElement, int ColumnElement) const;
	float& operator()(int RowElement, int ColumnElement);

	// Basic Addition and Subtraction
	float2x4 operator-() const;
	float2x4 operator+(const float2x4& Rhs) const;
	float2x4 operator-(const float2x4& Rhs) const;

	float2x4& operator+=(const float2x4& Rhs);
	float2x4& operator-=(const float2x4& Rhs);

	// Multiply column vector
	float2 operator*(const float4& Rhs) const;

	// Scalar Multiplication
	float2x4 operator*(float Rhs) const;
	float2x4 operator/(float Rhs) const;

	void setr(const float4& Row1, const float4& Row2);
	void setc(const float2& Col1, const float2& Col2, const float2& Col3, const float2& Col4);

};

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float2x4& Arg);
#endif // MATH_ENABLE_IO


#endif // !GEODESUKA_CORE_MATH_FLOAT2X4_H

