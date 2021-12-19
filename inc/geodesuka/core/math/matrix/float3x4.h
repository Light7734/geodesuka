#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT3X4_H
#define GEODESUKA_CORE_MATH_FLOAT3X4_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../number/type.h"

#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"


union float3x4 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	struct {
		float xx, xy, xz, xt;
		float yx, yy, yz, yt;
		float zx, zy, zz, zt;
	};
	//struct {
	//	float4 x, y, z;
	//};
	//float4 vptr[3];
	float aptr[3][4];
#else
	// Column Major Memory Layout
	struct {
		float xx, yx, zx;
		float xy, yy, zy;
		float xz, yz, zz;
		float xt, yt, zt;
	};
	//struct {
	//	float3 x, y, z, t;
	//};
	//float3 vptr[4];
	float aptr[4][3];
#endif // !COL_MAJOR_MEMORY_LAYOUT
	float ptr[3 * 4];

	float3x4() :
		xx(0.0), xy(0.0), xz(0.0), xt(0.0),
		yx(0.0), yy(0.0), yz(0.0), yt(0.0),
		zx(0.0), zy(0.0), zz(0.0), zt(0.0)
	{}
	float3x4(
		float XX, float XY, float XZ, float XT,
		float YX, float YY, float YZ, float YT,
		float ZX, float ZY, float ZZ, float ZT
	) :
		xx(XX), xy(XY), xz(XZ), xt(XT),
		yx(YX), yy(YY), yz(YZ), yt(YT),
		zx(ZX), zy(ZY), zz(ZZ), zt(ZT)
	{}
	~float3x4() {}

	// Access elements of matrix in standard notation.
	float operator()(int RowElement, int ColumnElement) const;
	float& operator()(int RowElement, int ColumnElement);

	// Basic Addition and Subtraction
	float3x4 operator-() const;
	float3x4 operator+(const float3x4& Rhs) const;
	float3x4 operator-(const float3x4& Rhs) const;

	float3x4& operator+=(const float3x4& Rhs);
	float3x4& operator-=(const float3x4& Rhs);

	// Multiply column vector
	float3 operator*(const float4& Rhs) const;

	// Scalar Multiplication
	float3x4 operator*(float Rhs) const;
	float3x4 operator/(float Rhs) const;

	// Set Rows/Columns using respective vectors
	void setr(const float4& Row1, const float4& Row2, const float4& Row3);
	void setc(const float3& Col1, const float3& Col2, const float3& Col3, const float3& Col4);

};

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float3x4& Arg);
#endif // MATH_ENABLE_IO

#endif // !GEODESUKA_CORE_MATH_FLOAT3X4_H
