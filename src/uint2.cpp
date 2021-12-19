#include <geodesuka/core/math/vector/uint2.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

uint2& uint2::operator=(uint aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	return *this;
}

uint2& uint2::operator=(const uint2& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

uint2& uint2::operator=(uint2&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

uint uint2::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

uint& uint2::operator[](int aIndex) {
	return this->ptr[aIndex];
}

uint2 uint2::operator+(uint aRhs) const {
	return uint2(this->x + aRhs, this->y + aRhs);
}

uint2 uint2::operator+(const uint2& aRhs) const {
	return uint2(this->x + aRhs.x, this->y + aRhs.y);
}

uint2 uint2::operator-(uint aRhs) const {
	return uint2(this->x - aRhs, this->y - aRhs);
}

uint2 uint2::operator-(const uint2& aRhs) const {
	return uint2(this->x - aRhs.x, this->y - aRhs.y);
}

uint2& uint2::operator+=(uint aRhs) {
	*this = *this + aRhs;
	return *this;
}

uint2& uint2::operator+=(const uint2& aRhs) {
	*this = *this + aRhs;
	return *this;
}

uint2& uint2::operator-=(uint aRhs) {
	*this = *this - aRhs;
	return *this;
}

uint2& uint2::operator-=(const uint2& aRhs) {
	*this = *this - aRhs;
	return *this;
}

uint2 uint2::operator*(uint aRhs) const {
	return uint2(this->x * aRhs, this->y * aRhs);
}

uint2 uint2::operator/(uint aRhs) const {
	return uint2(this->x / aRhs, this->y / aRhs);
}

uint2& uint2::operator*=(uint aRhs) {
	*this = *this * aRhs;
	return *this;
}

uint2& uint2::operator/=(uint aRhs) {
	*this = *this / aRhs;
	return *this;
}

uint uint2::operator*(const uint2& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y);
}

uint2 operator+(uint aLhs, const uint2& aRhs) {
	return aRhs + aLhs;
}

uint2 operator-(uint aLhs, const uint2& aRhs) {
	return uint2(aLhs - aRhs.x, aLhs - aRhs.y);
}

uint2 operator*(uint aLhs, const uint2& aRhs) {
	return aRhs * aLhs;
}
