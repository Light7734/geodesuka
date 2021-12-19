#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT3X2_H
#define GEODESUKA_CORE_MATH_FLOAT3X2_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../number/type.h"

#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"

//struct float3x2 {
//	float a11, a21;
//	float a12, a22;
//	float a13, a23;
//};

union float3x2 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	struct {
		float xx, xy;
		float yx, yy;
		float zx, zy;
	};
	// Row Vectors
	//struct {
	//	float2 x;
	//	float2 y;
	//	float2 z;
	//};
	//float3 vptr[2];
	float aptr[3][2];
#else
	// Column Major Memory Layout
	struct {
		float xx, yx, zx;
		float xy, yy, zy;
	};
	// Column Vectors
	//struct {
	//	float3 x, y;
	//};
	//float2 vptr[3];
	float aptr[3][2];
#endif // !COL_MAJOR_MEMORY_LAYOUT
	float ptr[2 * 3];

	float3x2() :
		xx(0.0), xy(0.0),
		yx(0.0), yy(0.0),
		zx(0.0), zy(0.0)
	{}
	float3x2(
		float XX, float XY,
		float YX, float YY,
		float ZX, float ZY
	) :
		xx(XX), xy(XY),
		yx(YX), yy(YY),
		zx(ZX), zy(ZY)
	{}
	~float3x2() {}

	// Access elements of matrix in standard notation.
	float operator()(int RowElement, int ColumnElement) const;
	float& operator()(int RowElement, int ColumnElement);

	// Basic Addition and Subtraction
	float3x2 operator-() const;
	float3x2 operator+(const float3x2& Rhs) const;
	float3x2 operator-(const float3x2& Rhs) const;

	float3x2& operator+=(const float3x2& Rhs);
	float3x2& operator-=(const float3x2& Rhs);

	// Multiply column vector
	float3 operator*(const float2& Rhs) const;

	// Scalar Multiplication
	float3x2 operator*(float Rhs) const;
	float3x2 operator/(float Rhs) const;

	void setr(const float2& Row1, const float2& Row2, const float2& Row3);
	void setc(const float3& Col1, const float3& Col2);

};

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float3x2& Arg);
#endif // MATH_ENABLE_IO


#endif // !GEODESUKA_CORE_MATH_FLOAT3X2_H

