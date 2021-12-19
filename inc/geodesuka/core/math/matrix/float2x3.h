#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT2X3_H
#define GEODESUKA_CORE_MATH_FLOAT2X3_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"

//float A[3][2] = { {0,1}, {2,3}, {4,5} };
//float A[2][3] = { {0,1,2}, {3,4,5} };

union float2x3 {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	struct {
		float xx, xy, xz;
		float yx, yy, yz;
	};
	// Row Vectors
	//struct {
	//	float3 x;
	//	float3 y;
	//};
	//float3 vptr[2];
	float aptr[2][3];
#endif
#ifdef COL_MAJOR_MEMORY_LAYOUT
	// Column Major Memory Layout
	struct {
		float xx, yx;
		float xy, yy;
		float xz, yz;
	};
	// Column Vectors
	//struct {
	//	float2 x, y, z;
	//};
	//float2 vptr[3];
	float aptr[3][2];
#endif
	float ptr[2 * 3];

	float2x3() :
		xx(0.0), xy(0.0), xz(0.0),
		yx(0.0), yy(0.0), yz(0.0)
	{}
	float2x3(
		float XX, float XY, float XZ,
		float YX, float YY, float YZ
	) :
		xx(XX), xy(XY), xz(XZ),
		yx(YX), yy(YY), yz(YZ)
	{}
	//float2x3(const float2& Col1, const float2& Col2, const float2& Col3) :
	//	xx(Col1.x), xy(Col2.x), xz(Col3.x),
	//	yx(Col1.y), yy(Col2.y), yz(Col3.y)
	//{}
	float2x3(const float2x3& Arg);
	~float2x3() {}

	float2x3& operator=(const float2x3& Rhs);

	float operator()(int RowElement, int ColumnElement) const;
	float& operator()(int RowElement, int ColumnElement);

	// Basic Addition and Subtraction
	float2x3 operator-() const;
	float2x3 operator+(const float2x3& Rhs) const;
	float2x3 operator-(const float2x3& Rhs) const;

	float2x3& operator+=(const float2x3& Rhs);
	float2x3& operator-=(const float2x3& Rhs);

	// Multiply column vector
	float2 operator*(const float3& Rhs) const;

	// Scalar Multiplication/Division
	float2x3 operator*(float Rhs) const;
	float2x3 operator/(float Rhs) const;

	void setr(const float3& Row1, const float3& Row2);
	void setc(const float2& Col1, const float2& Col2, const float2& Col3);

};

float3 operator*(const float2& Lhs, const float2x3& Rhs);
float2x3 operator*(float Lhs, const float2x3& Rhs);

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float2x3& Arg);
#endif // MATH_ENABLE_IO

#endif // !GEODESUKA_CORE_MATH_FLOAT2X3_H
