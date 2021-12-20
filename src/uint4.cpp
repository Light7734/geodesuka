#include <geodesuka/core/math/vector/uint4.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

uint4& uint4::operator=(uint aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	this->t = aRhs;
	return *this;
}

//uint4& uint4::operator=(const uint4& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	this->t = aRhs.t;
//	return *this;
//}
//
//uint4& uint4::operator=(uint4&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	this->t = aRhs.t;
//	return *this;
//}

uint uint4::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

uint& uint4::operator[](int aIndex) {
	return this->ptr[aIndex];
}

uint4 uint4::operator+(uint aRhs) const {
	return uint4(this->x + aRhs, this->y + aRhs, this->z + aRhs, this->t + aRhs);
}

uint4 uint4::operator+(const uint4& aRhs) const {
	return uint4(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z, this->t + aRhs.t);
}

uint4 uint4::operator-(uint aRhs) const {
	return uint4(this->x - aRhs, this->y - aRhs, this->z - aRhs, this->t - aRhs);
}

uint4 uint4::operator-(const uint4& aRhs) const {
	return uint4(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z, this->t - aRhs.t);
}

uint4& uint4::operator+=(uint aRhs) {
	*this = *this + aRhs;
	return *this;
}

uint4& uint4::operator+=(const uint4& aRhs) {
	*this = *this + aRhs;
	return *this;
}

uint4& uint4::operator-=(uint aRhs) {
	*this = *this - aRhs;
	return *this;
}

uint4& uint4::operator-=(const uint4& aRhs) {
	*this = *this - aRhs;
	return *this;
}

uint4 uint4::operator*(uint aRhs) const {
	return uint4(this->x * aRhs, this->y * aRhs, this->z * aRhs, this->t * aRhs);
}

uint4 uint4::operator/(uint aRhs) const {
	return uint4(this->x / aRhs, this->y / aRhs, this->z / aRhs, this->t / aRhs);
}

uint4& uint4::operator*=(uint aRhs) {
	*this = *this * aRhs;
	return *this;
}

uint4& uint4::operator/=(uint aRhs) {
	*this = *this / aRhs;
	return *this;
}

uint uint4::operator*(const uint4& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z + this->t * aRhs.t);
}

uint4 operator+(uint aLhs, const uint4& aRhs) {
	return aRhs + aLhs;
}

uint4 operator-(uint aLhs, const uint4& aRhs) {
	return uint4(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z, aLhs - aRhs.t);
}

uint4 operator*(uint aLhs, const uint4& aRhs) {
	return aRhs * aLhs;
}
