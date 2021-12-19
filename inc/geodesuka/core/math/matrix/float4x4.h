#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT4X4_H
#define GEODESUKA_CORE_MATH_FLOAT4X4_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../vector/int2.h"

#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"

#include "float2x2.h"
#include "float3x3.h"

union float4x4 {
	static const float4x4 I;
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	struct {
		float xx, xy, xz, xt;
		float yx, yy, yz, yt;
		float zx, zy, zz, zt;
		float tx, ty, tz, tt;
	};
#else
	// Column Major Memory Layout
	struct {
		float xx, yx, zx, tx;
		float xy, yy, zy, ty;
		float xz, yz, zz, tz;
		float xt, yt, zt, tt;
	};
#endif // !COL_MAJOR_MEMORY_LAYOUT
	//struct {
	//	float4 x, y, z, t;
	//};
	//float4 vptr[4];
	float aptr[4][4];
	float ptr[4 * 4];

	float4x4() :
		xx(0.0), xy(0.0), xz(0.0), xt(0.0),
		yx(0.0), yy(0.0), yz(0.0), yt(0.0),
		zx(0.0), zy(0.0), zz(0.0), zt(0.0),
		tx(0.0), ty(0.0), tz(0.0), tt(0.0)
	{}
	float4x4(
		float XX, float XY, float XZ, float XT,
		float YX, float YY, float YZ, float YT,
		float ZX, float ZY, float ZZ, float ZT,
		float TX, float TY, float TZ, float TT
	) :
		xx(XX), xy(XY), xz(XZ), xt(XT),
		yx(YX), yy(YY), yz(YZ), yt(YT),
		zx(ZX), zy(ZY), zz(ZZ), zt(ZT),
		tx(TX), ty(TY), tz(TZ), tt(TT)
	{}
	float4x4(
		const float2x2& A, const float2x2& B,
		const float2x2& C, const float2x2& D
	) :
		xx(A.xx), xy(A.xy), xz(B.xx), xt(B.xy),
		yx(A.yx), yy(A.yy), yz(B.yx), yt(B.yy),
		zx(C.xx), zy(C.xy), zz(D.xx), zt(D.xy),
		tx(C.yx), ty(C.yy), tz(D.yx), tt(D.yy)
	{}
	float4x4(const float4& Col1, const float4& Col2, const float4& Col3, const float4& Col4) :
		xx(Col1.x), xy(Col2.x), xz(Col3.x), xt(Col4.x),
		yx(Col1.y), yy(Col2.y), yz(Col3.y), yt(Col4.y),
		zx(Col1.z), zy(Col2.z), zz(Col3.z), zt(Col4.z),
		tx(Col1.t), ty(Col2.t), tz(Col3.t), tt(Col4.t)
	{}
	~float4x4() {}

	// Access elements of matrix in standard notation.
	float operator()(int RowElement, int ColumnElement) const;
	float& operator()(int RowElement, int ColumnElement);

	float4x4 operator-() const;
	float4x4 operator+(const float4x4& Rhs) const;
	float4x4 operator-(const float4x4& Rhs) const;
	float4x4 operator*(const float4x4& Rhs) const;

	float4x4& operator+=(const float4x4& Rhs);
	float4x4& operator-=(const float4x4& Rhs);
	float4x4& operator*=(const float4x4& Rhs);

	// Multiply column vector
	float4 operator*(const float4& Rhs) const;
	// Scalar Multiplication
	float4x4 operator*(float Rhs) const;
	float4x4 operator/(float Rhs) const;

	float3x3 sub(int RowElement, int ColumnElement) const;
	void setr(const float4& Row1, const float4& Row2, const float4& Row3, const float4& Row4);
	void setc(const float4& Col1, const float4& Col2, const float4& Col3, const float4& Col4);

};

float4 operator*(const float4& Lhs, const float4x4& Rhs);
float4x4 operator*(float Lhs, const float4x4& Rhs);

float det(const float4x4& Arg);
float tr(const float4x4& Arg);
//float4x4 diag(const float4x4& Arg);
float4x4 transpose(const float4x4& Arg);
//float4x4 inverse(const float4x4& Arg);

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float4x4& Arg);
#endif // MATH_ENABLE_IO


#endif // !GEODESUKA_CORE_MATH_FLOAT4X4_H
