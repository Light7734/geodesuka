#pragma once
#ifndef GEODESUKA_CORE_MATH_REAL2_H
#define GEODESUKA_CORE_MATH_REAL2_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

//#include "../number/type.h"

union float2 {
	struct {
		float x, y;
	};
	struct {
		float a, b;
	};
	float ptr[2];

	float2();
	~float2();

#ifdef CS_PLEB_NOTATION
	float2(float Val); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
	float2(float ValX, float ValY);
	float2(const float2& Val);

#ifdef CS_PLEB_NOTATION
	float2& operator=(float Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
	float2& operator=(const float2& Rhs);

	float operator[](int Index) const;
	float& operator[](int Index);

	float2 operator-() const;
	float2 operator+(const float2& Rhs) const;
	float2 operator-(const float2& Rhs) const;
	float operator*(const float2& Rhs) const;
	float operator^(const float2& Rhs) const;

	float2& operator+=(const float2& Rhs);
	float2& operator-=(const float2& Rhs);

#ifdef CS_PLEB_NOTATION
	float2 operator+(float Rhs) const; /* Technically not legal, but useful */
	float2 operator-(float Rhs) const; /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
	float2 operator*(float Rhs) const;
	float2 operator/(float Rhs) const;

#ifdef CS_PLEB_NOTATION
	float2& operator+=(float Rhs); /* Technically not legal, but useful */
	float2& operator-=(float Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
	float2& operator*=(float Rhs);
	float2& operator/=(float Rhs);

};

#ifdef CS_PLEB_NOTATION
float2 operator+(float Lhs, const float2& Rhs); /* Technically not legal, but useful */
float2 operator-(float Lhs, const float2& Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
float2 operator*(float Lhs, const float2& Rhs);
#ifdef CS_PLEB_NOTATION
float2 operator/(float Lhs, const float2& Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION

float length(const float2& Arg);
float2 normalize(const float2& Arg);

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& os, const float2& v);
#endif // MATH_ENABLE_IO


#endif // !GEODESUKA_CORE_MATH_REAL2_H
