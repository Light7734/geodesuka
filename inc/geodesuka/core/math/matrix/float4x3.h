#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT4X3_H
#define GEODESUKA_CORE_MATH_FLOAT4X3_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../number/type.h"

#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"

//struct float4x3 {
//	float xx, yx, zx;
//	float xy, yy, zy;
//	float xz, yz, zz;
//	float xt, yt, zt;
//};

union float4x3 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	struct {
		float xx, xy, xz;
		float yx, yy, yz;
		float zx, zy, zz;
		float tx, ty, tz;
	};
	// Row vectors
	//struct {
	//	float3 x, y, z, t;
	//};
	//float3 vptr[4];
	float aptr[4][3];
#else
	// Column Major Memory Layout
	struct {
		float xx, yx, zx, tx;
		float xy, yy, zy, ty;
		float xz, yz, zz, tz;
	};
	// Column Vectors
	//struct {
	//	float4 x, y, z;
	//};
	//float4 vptr[3];
	float aptr[3][4];
#endif // !COL_MAJOR_MEMORY_LAYOUT
	float ptr[4 * 3];

	float4x3() :
		xx(0.0), xy(0.0), xz(0.0),
		yx(0.0), yy(0.0), yz(0.0),
		zx(0.0), zy(0.0), zz(0.0),
		tx(0.0), ty(0.0), tz(0.0)
	{}
	float4x3(
		float XX, float XY, float XZ,
		float YX, float YY, float YZ,
		float ZX, float ZY, float ZZ,
		float TX, float TY, float TZ
	) :
		xx(XX), xy(XY), xz(XZ),
		yx(YX), yy(YY), yz(YZ),
		zx(ZX), zy(ZY), zz(ZZ),
		tx(TX), ty(TY), tz(TZ)
	{}
	~float4x3() {}

	// Access elements of matrix in standard notation.
	float operator()(int RowElement, int ColumnElement) const;
	float& operator()(int RowElement, int ColumnElement);

	// Basic Addition and Subtraction
	float4x3 operator-() const;
	float4x3 operator+(const float4x3& Rhs) const;
	float4x3 operator-(const float4x3& Rhs) const;

	float4x3& operator+=(const float4x3& Rhs);
	float4x3& operator-=(const float4x3& Rhs);

	// Multiply column vector
	float4 operator*(const float3& Rhs) const;

	// Scalar Multiplication
	float4x3 operator*(float Rhs) const;
	float4x3 operator/(float Rhs) const;

	// Set Rows/Columns using respective vectors
	void setr(const float3& Row1, const float3& Row2, const float3& Row3, const float3& Row4);
	void setc(const float4& Col1, const float4& Col2, const float4& Col3);

};

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float4x3& Arg);
#endif // MATH_ENABLE_IO

#endif // !GEODESUKA_CORE_MATH_FLOAT4X3_H

