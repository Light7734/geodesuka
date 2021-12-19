#include <geodesuka/core/math/vector/ushort2.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>


ushort2& ushort2::operator=(ushort aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	return *this;
}

ushort2& ushort2::operator=(const ushort2& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

ushort2& ushort2::operator=(ushort2&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

ushort ushort2::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

ushort& ushort2::operator[](int aIndex) {
	return this->ptr[aIndex];
}

ushort2 ushort2::operator+(ushort aRhs) const {
	return ushort2(this->x + aRhs, this->y + aRhs);
}

ushort2 ushort2::operator+(const ushort2& aRhs) const {
	return ushort2(this->x + aRhs.x, this->y + aRhs.y);
}

ushort2 ushort2::operator-(ushort aRhs) const {
	return ushort2(this->x - aRhs, this->y - aRhs);
}

ushort2 ushort2::operator-(const ushort2& aRhs) const {
	return ushort2(this->x - aRhs.x, this->y - aRhs.y);
}

ushort2& ushort2::operator+=(ushort aRhs) {
	*this = *this + aRhs;
	return *this;
}

ushort2& ushort2::operator+=(const ushort2& aRhs) {
	*this = *this + aRhs;
	return *this;
}

ushort2& ushort2::operator-=(ushort aRhs) {
	*this = *this - aRhs;
	return *this;
}

ushort2& ushort2::operator-=(const ushort2& aRhs) {
	*this = *this - aRhs;
	return *this;
}

ushort2 ushort2::operator*(ushort aRhs) const {
	return ushort2(this->x * aRhs, this->y * aRhs);
}

ushort2 ushort2::operator/(ushort aRhs) const {
	return ushort2(this->x / aRhs, this->y / aRhs);
}

ushort2& ushort2::operator*=(ushort aRhs) {
	*this = *this * aRhs;
	return *this;
}

ushort2& ushort2::operator/=(ushort aRhs) {
	*this = *this / aRhs;
	return *this;
}

ushort ushort2::operator*(const ushort2& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y);
}

ushort2 operator+(ushort aLhs, const ushort2& aRhs) {
	return aRhs + aLhs;
}

ushort2 operator-(ushort aLhs, const ushort2& aRhs) {
	return ushort2(aLhs - aRhs.x, aLhs - aRhs.y);
}

ushort2 operator*(ushort aLhs, const ushort2& aRhs) {
	return aRhs * aLhs;
}



