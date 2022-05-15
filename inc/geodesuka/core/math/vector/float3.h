#pragma once
#ifndef GEODESUKA_CORE_MATH_FLOAT3_H
#define GEODESUKA_CORE_MATH_FLOAT3_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../number/type.h"


union float3 {
	struct {
		float x, y, z;
	};
	struct {
		float r, g, b;
	};
	float ptr[3];

	float3();
	~float3();

#ifdef CS_PLEB_NOTATION
	float3(float Val);
#endif // CS_PLEB_NOTATION
	float3(float ValX, float ValY, float ValZ);
	float3(const float3& Val);
	//float3(float3&& RR);

#ifdef CS_PLEB_NOTATION
	float3& operator=(float Rhs);
#endif // CS_PLEB_NOTATION
	//float3& operator=(float X, float Y, float Z);
	float3& operator=(const float3& Rhs);
	//float3& operator=(float3&& Rhs);

	float operator[](int Index) const;
	float& operator[](int Index);

	float3 operator-() const;
	float3 operator+(const float3& Rhs) const;
	float3 operator-(const float3& Rhs) const;
	float operator*(const float3& Rhs) const;
	float3 operator^(const float3& Rhs) const;

	float3& operator+=(const float3& Rhs);
	float3& operator-=(const float3& Rhs);
	float3& operator^=(const float3& Rhs);

#ifdef CS_PLEB_NOTATION
	float3 operator+(float Rhs) const; /* Technically not legal, but useful */
	float3 operator-(float Rhs) const; /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
	float3 operator*(float Rhs) const;
	float3 operator/(float Rhs) const;

#ifdef CS_PLEB_NOTATION
	float3& operator+=(float Rhs); /* Technically not legal, but useful */
	float3& operator-=(float Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
	float3& operator*=(float Rhs);
	float3& operator/=(float Rhs);

};

#ifdef CS_PLEB_NOTATION
float3 operator+(float Lhs, const float3& Rhs); /* Technically not legal, but useful */
float3 operator-(float Lhs, const float3& Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION
float3 operator*(float Lhs, const float3& Rhs);
#ifdef CS_PLEB_NOTATION
float3 operator/(float Lhs, const float3& Rhs); /* Technically not legal, but useful */
#endif // CS_PLEB_NOTATION

float length(const float3& Arg);
float3 normalize(const float3& Arg);

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& os, const float3& v);
#endif // MATH_ENABLE_IO

#endif // !GEODESUKA_CORE_MATH_FLOAT3_H
