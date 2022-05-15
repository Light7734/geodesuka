#include <geodesuka/core/math/vector/float3.h>

#include <string.h>

#include <cmath>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/number/type.h>


	float3::float3() {
		this->x = 0.0; this->y = 0.0; this->z = 0.0;
	}

	float3::~float3() {}
#ifdef CS_PLEB_NOTATION
	float3::float3(float Val) {
		this->x = Val; this->y = Val; this->z = Val;
	}
#endif // CS_PLEB_NOTATION
	float3::float3(float ValX, float ValY, float ValZ) {
		this->x = ValX; this->y = ValY; this->z = ValZ;
	}

	float3::float3(const float3& Val) {
		memcpy(this->ptr, Val.ptr, 3 * sizeof(float));
	}
#ifdef CS_PLEB_NOTATION
	float3& float3::operator=(float Rhs) {
		this->x = Rhs; this->y = Rhs; this->z = Rhs;
		return *this;
	}
#endif // CS_PLEB_NOTATION
	float3& float3::operator=(const float3& Rhs) {
		memcpy(this->ptr, Rhs.ptr, 3 * sizeof(float));
		return *this;
	}

	float float3::operator[](int Index) const {
		return this->ptr[Index];
	}

	float& float3::operator[](int Index) {
		return this->ptr[Index];
	}

	float3 float3::operator-() const {
		return float3(-this->x, -this->y, -this->z);
	}

	float3 float3::operator+(const float3& Rhs) const {
		return float3(this->x + Rhs.x, this->y + Rhs.y, this->z + Rhs.z);
	}

	float3 float3::operator-(const float3& Rhs) const {
		return float3(this->x - Rhs.x, this->y - Rhs.y, this->z - Rhs.z);
	}

	float float3::operator*(const float3& Rhs) const {
		return (this->x * Rhs.x + this->y * Rhs.y + this->z * Rhs.z);
	}

	float3 float3::operator^(const float3& Rhs) const {
		return float3(
			this->y * Rhs.z - this->z * Rhs.y,
			this->z * Rhs.x - this->x * Rhs.z,
			this->x * Rhs.y - this->y * Rhs.x
		);
	}

	float3& float3::operator+=(const float3& Rhs) {
		*this = *this + Rhs;
		return *this;
	}

	float3& float3::operator-=(const float3& Rhs) {
		*this = *this - Rhs;
		return *this;
	}

	float3& float3::operator^=(const float3& Rhs) {
		*this = *this ^ Rhs;
		return *this;
	}
#ifdef CS_PLEB_NOTATION
	float3 float3::operator+(float Rhs) const {
		return float3(this->x + Rhs, this->y + Rhs, this->z + Rhs);
	}

	float3 float3::operator-(float Rhs) const {
		return float3(this->x - Rhs, this->y - Rhs, this->z - Rhs);
	}
#endif // CS_PLEB_NOTATION
	float3 float3::operator*(float Rhs) const {
		return float3(this->x * Rhs, this->y * Rhs, this->z * Rhs);
	}

	float3 float3::operator/(float Rhs) const {
		return float3(this->x / Rhs, this->y / Rhs, this->z / Rhs);
	}
#ifdef CS_PLEB_NOTATION
	float3& float3::operator+=(float Rhs) {
		*this = *this + Rhs;
		return *this;
	}

	float3& float3::operator-=(float Rhs) {
		*this = *this - Rhs;
		return *this;
	}
#endif // CS_PLEB_NOTATION
	float3& float3::operator*=(float Rhs) {
		*this = *this * Rhs;
		return *this;
	}

	float3& float3::operator/=(float Rhs) {
		*this = *this / Rhs;
		return *this;
	}
#ifdef CS_PLEB_NOTATION
	float3 operator+(float Lhs, const float3& Rhs) {
		return float3(Lhs + Rhs.x, Lhs + Rhs.y, Lhs + Rhs.z);
	}

	float3 operator-(float Lhs, const float3& Rhs) {
		return float3(Lhs - Rhs.x, Lhs - Rhs.y, Lhs - Rhs.z);
	}
#endif // CS_PLEB_NOTATION
	float3 operator*(float Lhs, const float3& Rhs) {
		return float3(Lhs * Rhs.x, Lhs * Rhs.y, Lhs * Rhs.z);
	}
#ifdef CS_PLEB_NOTATION
	float3 operator/(float Lhs, const float3& Rhs) {
		return float3(Lhs / Rhs.x, Lhs / Rhs.y, Lhs / Rhs.z);
	}
#endif // CS_PLEB_NOTATION
	float length(const float3& Arg) {
		return sqrt(Arg * Arg);
	}

	float3 normalize(const float3& Arg) {
		return (Arg / length(Arg));
	}

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& os, const float3& v) {
		os << v.x << "ex + " << v.y << "ey + " << v.z << "ez";
		return os;
	}
#endif // MATH_ENABLE_IO

