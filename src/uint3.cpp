#include <geodesuka/core/math/vector/uint3.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

uint3& uint3::operator=(uint aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	return *this;
}

//uint3& uint3::operator=(const uint3& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	return *this;
//}
//
//uint3& uint3::operator=(uint3&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	return *this;
//}

uint uint3::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

uint& uint3::operator[](int aIndex) {
	return this->ptr[aIndex];
}

uint3 uint3::operator+(uint aRhs) const {
	return uint3(this->x + aRhs, this->y + aRhs, this->z + aRhs);
}

uint3 uint3::operator+(const uint3& aRhs) const {
	return uint3(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z);
}

uint3 uint3::operator-(uint aRhs) const {
	return uint3(this->x - aRhs, this->y - aRhs, this->z - aRhs);
}

uint3 uint3::operator-(const uint3& aRhs) const {
	return uint3(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z);
}

uint3& uint3::operator+=(uint aRhs) {
	*this = *this + aRhs;
	return *this;
}

uint3& uint3::operator+=(const uint3& aRhs) {
	*this = *this + aRhs;
	return *this;
}

uint3& uint3::operator-=(uint aRhs) {
	*this = *this - aRhs;
	return *this;
}

uint3& uint3::operator-=(const uint3& aRhs) {
	*this = *this - aRhs;
	return *this;
}

uint3 uint3::operator*(uint aRhs) const {
	return uint3(this->x * aRhs, this->y * aRhs, this->z * aRhs);
}

uint3 uint3::operator/(uint aRhs) const {
	return uint3(this->x / aRhs, this->y / aRhs, this->z / aRhs);
}

uint3& uint3::operator*=(uint aRhs) {
	*this = *this * aRhs;
	return *this;
}

uint3& uint3::operator/=(uint aRhs) {
	*this = *this / aRhs;
	return *this;
}

uint uint3::operator*(const uint3& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z);
}

uint3 operator+(uint aLhs, const uint3& aRhs) {
	return aRhs + aLhs;
}

uint3 operator-(uint aLhs, const uint3& aRhs) {
	return uint3(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z);
}

uint3 operator*(uint aLhs, const uint3& aRhs) {
	return aRhs * aLhs;
}

