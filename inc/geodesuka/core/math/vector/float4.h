#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT4_H
#define GEODESUKA_CORE_MATH_FLOAT4_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../number/type.h"

union float4 {
	struct {
		float x, y, z, t;
	};
	struct {
		float r, g, b, a;
	};
	float ptr[4];

	float4();
	~float4();

#ifdef CS_PLEB_NOTATION
	float4(float Val);
#endif // CS_PLEB_NOTATION
	float4(float ValX, float ValY, float ValZ, float ValT);
	float4(const float4& Val);

#ifdef CS_PLEB_NOTATION
	float4& operator=(float Rhs);
#endif // CS_PLEB_NOTATION
	float4& operator=(const float4& Rhs);

	float operator[](int Index) const;
	float& operator[](int Index);

	float4 operator-() const;
	float4 operator+(const float4& Rhs) const;
	float4 operator-(const float4& Rhs) const;
	float operator*(const float4& Rhs) const;

	float4& operator+=(const float4& Rhs);
	float4& operator-=(const float4& Rhs);

#ifdef CS_PLEB_NOTATION
	float4 operator+(float Rhs) const;
	float4 operator-(float Rhs) const;
#endif // CS_PLEB_NOTATION
	float4 operator*(float Rhs) const;
	float4 operator/(float Rhs) const;

#ifdef CS_PLEB_NOTATION
	float4& operator+=(float Rhs);
	float4& operator-=(float Rhs);
#endif // CS_PLEB_NOTATION
	float4& operator*=(float Rhs);
	float4& operator/=(float Rhs);

};

#ifdef CS_PLEB_NOTATION
float4 operator+(float Lhs, const float4& Rhs);
float4 operator-(float Lhs, const float4& Rhs);
#endif // CS_PLEB_NOTATION
float4 operator*(float Lhs, const float4& Rhs);
#ifdef CS_PLEB_NOTATION
float4 operator/(float Lhs, const float4& Rhs);
#endif // CS_PLEB_NOTATION

float length(const float4& Arg);
float4 normalize(const float4& Arg);

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& os, const float4& v);
#endif // MATH_ENABLE_IO

#endif // !GEODESUKA_CORE_MATH_FLOAT4_H
