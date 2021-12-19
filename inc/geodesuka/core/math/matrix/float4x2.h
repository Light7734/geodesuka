#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT4X2_H
#define GEODESUKA_CORE_MATH_FLOAT4X2_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../number/type.h"

#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"


union float4x2 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	struct {
		float xx, xy;
		float yx, yy;
		float zx, zy;
		float tx, ty;
	};
	// Row vectors
	//struct {
	//	float2 x, y, z, t;
	//};
	//float2 vptr[4];
	float aptr[4][2];
#else
	// Column Major Memory Layout
	struct {
		float xx, yx, zx, tx;
		float xy, yy, zy, ty;
	};
	// Column Vectors
	//struct {
	//	float4 x, y;
	//};
	//float4 vptr[2];
	float aptr[2][4];
#endif // !COL_MAJOR_MEMORY_LAYOUT
	float ptr[4 * 2];

	float4x2() :
		xx(0.0), xy(0.0),
		yx(0.0), yy(0.0),
		zx(0.0), zy(0.0),
		tx(0.0), ty(0.0)
	{}
	float4x2(
		float XX, float XY,
		float YX, float YY,
		float ZX, float ZY,
		float TX, float TY
	) :
		xx(XX), xy(XY),
		yx(YX), yy(YY),
		zx(ZX), zy(ZY),
		tx(TX), ty(TY)
	{}
	~float4x2() {}

	// Access elements of matrix in standard notation.
	float operator()(int RowElement, int ColumnElement) const;
	float& operator()(int RowElement, int ColumnElement);

	// Basic Addition and Subtraction
	float4x2 operator-() const;
	float4x2 operator+(const float4x2& Rhs) const;
	float4x2 operator-(const float4x2& Rhs) const;

	float4x2& operator+=(const float4x2& Rhs);
	float4x2& operator-=(const float4x2& Rhs);

	// Multiply column vector
	float4 operator*(const float2& Rhs) const;

	// Scalar Multiplication
	float4x2 operator*(float Rhs) const;
	float4x2 operator/(float Rhs) const;

	// Set Rows/Columns using respective vectors
	void setr(const float2& Row1, const float2& Row2, const float2& Row3, const float2& Row4);
	void setc(const float4& Col1, const float4& Col2);

};

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float4x2& Arg);
#endif // MATH_ENABLE_IO

#endif // !GEODESUKA_CORE_MATH_FLOAT4X2_H
