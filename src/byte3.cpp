#include <geodesuka/core/math/vector/byte3.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

byte3& byte3::operator=(byte aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	return *this;
}

byte3& byte3::operator=(const byte3& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	return *this;
}

byte3& byte3::operator=(byte3&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	return *this;
}

byte byte3::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

byte& byte3::operator[](int aIndex) {
	return this->ptr[aIndex];
}

byte3 byte3::operator-() const {
	return byte3(-this->x, -this->y, -this->z);
}

byte3 byte3::operator+(byte aRhs) const {
	return byte3(this->x + aRhs, this->y + aRhs, this->z + aRhs);
}

byte3 byte3::operator+(const byte3& aRhs) const {
	return byte3(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z);
}

byte3 byte3::operator-(byte aRhs) const {
	return byte3(this->x - aRhs, this->y - aRhs, this->z - aRhs);
}

byte3 byte3::operator-(const byte3& aRhs) const {
	return byte3(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z);
}

byte3& byte3::operator+=(byte aRhs) {
	*this = *this + aRhs;
	return *this;
}

byte3& byte3::operator+=(const byte3& aRhs) {
	*this = *this + aRhs;
	return *this;
}

byte3& byte3::operator-=(byte aRhs) {
	*this = *this - aRhs;
	return *this;
}

byte3& byte3::operator-=(const byte3& aRhs) {
	*this = *this - aRhs;
	return *this;
}

byte3 byte3::operator*(byte aRhs) const {
	return byte3(this->x * aRhs, this->y * aRhs, this->z * aRhs);
}

byte3 byte3::operator/(byte aRhs) const {
	return byte3(this->x / aRhs, this->y / aRhs, this->z / aRhs);
}

byte3& byte3::operator*=(byte aRhs) {
	*this = *this * aRhs;
	return *this;
}

byte3& byte3::operator/=(byte aRhs) {
	*this = *this / aRhs;
	return *this;
}

byte byte3::operator*(const byte3& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z);
}

byte3 byte3::operator^(const byte3& aRhs) const {
	return byte3(
		this->y * aRhs.z - this->z * aRhs.y,
		this->z * aRhs.x - this->x * aRhs.z,
		this->x * aRhs.y - this->y * aRhs.x
	);
}

byte3 operator+(byte aLhs, const byte3& aRhs) {
	return aRhs + aLhs;
}

byte3 operator-(byte aLhs, const byte3& aRhs) {
	return byte3(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z);
}

byte3 operator*(byte aLhs, const byte3& aRhs) {
	return aRhs * aLhs;
}

