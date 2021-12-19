#include <geodesuka/core/math/vector/byte4.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

byte4& byte4::operator=(byte aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	this->t = aRhs;
	return *this;
}

byte4& byte4::operator=(const byte4& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	this->t = aRhs.t;
	return *this;
}

byte4& byte4::operator=(byte4&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	this->t = aRhs.t;
	return *this;
}

byte byte4::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

byte& byte4::operator[](int aIndex) {
	return this->ptr[aIndex];
}

byte4 byte4::operator-() const {
	return byte4(-this->x, -this->y, -this->z, -this->t);
}

byte4 byte4::operator+(byte aRhs) const {
	return byte4(this->x + aRhs, this->y + aRhs, this->z + aRhs, this->t + aRhs);
}

byte4 byte4::operator+(const byte4& aRhs) const {
	return byte4(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z, this->t + aRhs.t);
}

byte4 byte4::operator-(byte aRhs) const {
	return byte4(this->x - aRhs, this->y - aRhs, this->z - aRhs, this->t - aRhs);
}

byte4 byte4::operator-(const byte4& aRhs) const {
	return byte4(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z, this->t - aRhs.t);
}

byte4& byte4::operator+=(byte aRhs) {
	*this = *this + aRhs;
	return *this;
}

byte4& byte4::operator+=(const byte4& aRhs) {
	*this = *this + aRhs;
	return *this;
}

byte4& byte4::operator-=(byte aRhs) {
	*this = *this - aRhs;
	return *this;
}

byte4& byte4::operator-=(const byte4& aRhs) {
	*this = *this - aRhs;
	return *this;
}

byte4 byte4::operator*(byte aRhs) const {
	return byte4(this->x * aRhs, this->y * aRhs, this->z * aRhs, this->t * aRhs);
}

byte4 byte4::operator/(byte aRhs) const {
	return byte4(this->x / aRhs, this->y / aRhs, this->z / aRhs, this->t / aRhs);
}

byte4& byte4::operator*=(byte aRhs) {
	*this = *this * aRhs;
	return *this;
}

byte4& byte4::operator/=(byte aRhs) {
	*this = *this / aRhs;
	return *this;
}

byte byte4::operator*(const byte4& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z + this->t * aRhs.t);
}

byte4 operator+(byte aLhs, const byte4& aRhs) {
	return aRhs + aLhs;
}

byte4 operator-(byte aLhs, const byte4& aRhs) {
	return byte4(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z, aLhs - aRhs.t);
}

byte4 operator*(byte aLhs, const byte4& aRhs) {
	return aRhs * aLhs;
}

