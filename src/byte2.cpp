#include <geodesuka/core/math/vector/byte2.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

byte2& byte2::operator=(byte aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	return *this;
}

byte2& byte2::operator=(const byte2& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

byte2& byte2::operator=(byte2&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

byte byte2::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

byte& byte2::operator[](int aIndex) {
	return this->ptr[aIndex];
}

byte2 byte2::operator-() const {
	return byte2(-this->x, -this->y);
}

byte2 byte2::operator+(byte aRhs) const {
	return byte2(this->x + aRhs, this->y + aRhs);
}

byte2 byte2::operator+(const byte2& aRhs) const {
	return byte2(this->x + aRhs.x, this->y + aRhs.y);
}

byte2 byte2::operator-(byte aRhs) const {
	return byte2(this->x - aRhs, this->y - aRhs);
}

byte2 byte2::operator-(const byte2& aRhs) const {
	return byte2(this->x - aRhs.x, this->y - aRhs.y);
}

byte2& byte2::operator+=(byte aRhs) {
	*this = *this + aRhs;
	return *this;
}

byte2& byte2::operator+=(const byte2& aRhs) {
	*this = *this + aRhs;
	return *this;
}

byte2& byte2::operator-=(byte aRhs) {
	*this = *this - aRhs;
	return *this;
}

byte2& byte2::operator-=(const byte2& aRhs) {
	*this = *this - aRhs;
	return *this;
}

byte2 byte2::operator*(byte aRhs) const {
	return byte2(this->x * aRhs, this->y * aRhs);
}

byte2 byte2::operator/(byte aRhs) const {
	return byte2(this->x / aRhs, this->y / aRhs);
}

byte2& byte2::operator*=(byte aRhs) {
	*this = *this * aRhs;
	return *this;
}

byte2& byte2::operator/=(byte aRhs) {
	*this = *this / aRhs;
	return *this;
}

byte byte2::operator*(const byte2& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y);
}

byte2 byte2::operator^(const byte2& aRhs) const {
	return (this->x * aRhs.y - this->y * aRhs.x);
}

byte2 operator+(byte aLhs, const byte2& aRhs) {
	return aRhs + aLhs;
}

byte2 operator-(byte aLhs, const byte2& aRhs) {
	return byte2(aLhs - aRhs.x, aLhs - aRhs.y);
}

byte2 operator*(byte aLhs, const byte2& aRhs) {
	return aRhs * aLhs;
}
