#include <geodesuka/core/math/vector/float2.h>

//// Standard C Libraries
////#include <assert.h>
//#include <stdint.h>
//#include <float.h>
//#include <limits.h>
//#include <math.h>

#include <cmath>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/number/type.h>


float2::float2() {
	this->x = 0.0; this->y = 0.0;
}

float2::~float2() {}
#ifdef CS_PLEB_NOTATION
float2::float2(float Val) {
	this->x = Val; this->y = Val;
}
#endif // CS_PLEB_NOTATION
float2::float2(float ValX, float ValY) {
	this->x = ValX; this->y = ValY;
}

float2::float2(const float2& Val) {
	this->x = Val.x; this->y = Val.y;
}
#ifdef CS_PLEB_NOTATION
float2& float2::operator=(float Rhs) {
	this->x = Rhs; this->y = Rhs;
	return *this;
}
#endif // CS_PLEB_NOTATION
float2& float2::operator=(const float2& Rhs) {
	this->x = Rhs.x; this->y = Rhs.y;
	return *this;
}

float float2::operator[](int Index) const {
	return this->ptr[Index];
}

float& float2::operator[](int Index) {
	return this->ptr[Index];
}

float2 float2::operator-() const {
	return float2(-this->x, -this->y);
}

float2 float2::operator+(const float2& Rhs) const {
	return float2(this->x + Rhs.x, this->y + Rhs.y);
}

float2 float2::operator-(const float2& Rhs) const {
	return float2(this->x - Rhs.x, this->y - Rhs.y);
}

float float2::operator*(const float2& Rhs) const {
	return (this->x * Rhs.x + this->y * Rhs.y);
}

float float2::operator^(const float2& Rhs) const {
	return (this->x * Rhs.y - this->y * Rhs.x);
}
float2& float2::operator+=(const float2& Rhs) {
	*this = *this + Rhs;
	return *this;
}
float2& float2::operator-=(const float2& Rhs) {
	*this = *this - Rhs;
	return *this;
}
#ifdef CS_PLEB_NOTATION
float2 float2::operator+(float Rhs) const {
	return float2(this->x + Rhs, this->y + Rhs);
}

float2 float2::operator-(float Rhs) const {
	return float2(this->x - Rhs, this->y - Rhs);
}
#endif // CS_PLEB_NOTATION
float2 float2::operator*(float Rhs) const {
	return float2(this->x * Rhs, this->y * Rhs);
}

float2 float2::operator/(float Rhs) const {
	return float2(this->x / Rhs, this->y / Rhs);
}
#ifdef CS_PLEB_NOTATION
float2& float2::operator+=(float Rhs) {
	*this = *this + Rhs;
	return *this;
}

float2& float2::operator-=(float Rhs) {
	*this = *this - Rhs;
	return *this;
}
#endif // CS_PLEB_NOTATION
float2& float2::operator*=(float Rhs) {
	*this = *this * Rhs;
	return *this;
}

float2& float2::operator/=(float Rhs) {
	*this = *this / Rhs;
	return *this;
}

#ifdef CS_PLEB_NOTATION
float2 operator+(float Lhs, const float2& Rhs) {
	return float2(Lhs + Rhs.x, Lhs + Rhs.y);
}

float2 operator-(float Lhs, const float2& Rhs) {
	return float2(Lhs - Rhs.x, Lhs - Rhs.y);
}
#endif // CS_PLEB_NOTATION
float2 operator*(float Lhs, const float2& Rhs) {
	return float2(Lhs * Rhs.x, Lhs * Rhs.y);
}
#ifdef CS_PLEB_NOTATION
float2 operator/(float Lhs, const float2& Rhs) {
	return float2(Lhs / Rhs.x, Lhs / Rhs.y);
}
#endif // CS_PLEB_NOTATION
float length(const float2& Arg) {
	return sqrt(Arg * Arg);
}

float2 normalize(const float2& Arg) {
	return (float2(Arg) / length(Arg));
}

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& os, const float2& v) {
	os << v.x << "ex + " << v.y << "ey";
	return os;
}
#endif // MATH_ENABLE_IO
