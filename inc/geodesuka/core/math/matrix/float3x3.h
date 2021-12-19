#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT3X3_H
#define GEODESUKA_CORE_MATH_FLOAT3X3_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../number/type.h"
#include "../vector/int2.h"

#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"

#include "float2x2.h"


union float3x3 {
	static const float3x3 I;
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	struct {
		float xx, xy, xz;
		float yx, yy, yz;
		float zx, zy, zz;
	};
#else
	// Column Major Memory Layout
	struct {
		float xx, yx, zx;
		float xy, yy, zy;
		float xz, yz, zz;
	};
#endif // !COL_MAJOR_MEMORY_LAYOUT
	//struct {
	//	float3 x, y, z;
	//};
	//float3 vptr[3];
	float aptr[3][3];
	float ptr[3 * 3];

	float3x3() :
		xx(0.0), xy(0.0), xz(0.0),
		yx(0.0), yy(0.0), yz(0.0),
		zx(0.0), zy(0.0), zz(0.0)
	{}
	float3x3(
		float XX, float XY, float XZ,
		float YX, float YY, float YZ,
		float ZX, float ZY, float ZZ
	) :
		xx(XX), xy(XY), xz(XZ),
		yx(YX), yy(YY), yz(YZ),
		zx(ZX), zy(ZY), zz(ZZ)
	{}
	float3x3(const float3& Col1, const float3& Col2, const float3& Col3);
	float3x3(const float3x3& Arg);
	~float3x3() {}

	float3x3& operator=(const float3x3& Rhs);

	// Access elements of matrix in standard notation.
	float operator()(int RowElement, int ColumnElement) const;
	float& operator()(int RowElement, int ColumnElement);

	//float operator[](int2 Index) const;
	//float& operator[](int2 Index);

	float3x3 operator-() const;
	float3x3 operator+(const float3x3& Rhs) const;
	float3x3 operator-(const float3x3& Rhs) const;
	float3x3 operator*(const float3x3& Rhs) const;

	float3x3& operator+=(const float3x3& Rhs);
	float3x3& operator-=(const float3x3& Rhs);
	float3x3& operator*=(const float3x3& Rhs);

	float3 operator*(const float3& Rhs) const;
	float3x3 operator*(float Rhs) const;
	float3x3 operator/(float Rhs) const;

	float2x2 sub(int RowElement, int ColumnElement) const;
	void setr(const float3& Row1, const float3& Row2, const float3& Row3);
	void setc(const float3& Col1, const float3& Col2, const float3& Col3);

	friend float3 operator*(const float3& Lhs, const float3x3& Rhs);
	friend float3x3 operator*(float Lhs, const float3x3& Rhs);

};

float det(const float3x3& Arg);
float tr(const float3x3& Arg);
float3x3 transpose(const float3x3& Arg);
float3x3 inverse(const float3x3& Arg);

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float3x3& Arg);
#endif // MATH_ENABLE_IO

#endif // !GEODESUKA_CORE_MATH_FLOAT3X3_H
