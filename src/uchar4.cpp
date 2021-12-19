#include <geodesuka/core/math/vector/uchar4.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

uchar4& uchar4::operator=(uchar aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	this->t = aRhs;
	return *this;
}

uchar4& uchar4::operator=(const uchar4& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	this->t = aRhs.t;
	return *this;
}

uchar4& uchar4::operator=(uchar4&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	this->t = aRhs.t;
	return *this;
}

uchar uchar4::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

uchar& uchar4::operator[](int aIndex) {
	return this->ptr[aIndex];
}

uchar4 uchar4::operator+(uchar aRhs) const {
	return uchar4(this->x + aRhs, this->y + aRhs, this->z + aRhs, this->t + aRhs);
}

uchar4 uchar4::operator+(const uchar4& aRhs) const {
	return uchar4(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z, this->t + aRhs.t);
}

uchar4 uchar4::operator-(uchar aRhs) const {
	return uchar4(this->x - aRhs, this->y - aRhs, this->z - aRhs, this->t - aRhs);
}

uchar4 uchar4::operator-(const uchar4& aRhs) const {
	return uchar4(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z, this->t - aRhs.t);
}

uchar4& uchar4::operator+=(uchar aRhs) {
	*this = *this + aRhs;
	return *this;
}

uchar4& uchar4::operator+=(const uchar4& aRhs) {
	*this = *this + aRhs;
	return *this;
}

uchar4& uchar4::operator-=(uchar aRhs) {
	*this = *this - aRhs;
	return *this;
}

uchar4& uchar4::operator-=(const uchar4& aRhs) {
	*this = *this - aRhs;
	return *this;
}

uchar4 uchar4::operator*(uchar aRhs) const {
	return uchar4(this->x * aRhs, this->y * aRhs, this->z * aRhs, this->t * aRhs);
}

uchar4 uchar4::operator/(uchar aRhs) const {
	return uchar4(this->x / aRhs, this->y / aRhs, this->z / aRhs, this->t / aRhs);
}

uchar4& uchar4::operator*=(uchar aRhs) {
	*this = *this * aRhs;
	return *this;
}

uchar4& uchar4::operator/=(uchar aRhs) {
	*this = *this / aRhs;
	return *this;
}

uchar uchar4::operator*(const uchar4& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z + this->t * aRhs.t);
}

uchar4 operator+(uchar aLhs, const uchar4& aRhs) {
	return aRhs + aLhs;
}

uchar4 operator-(uchar aLhs, const uchar4& aRhs) {
	return uchar4(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z, aLhs - aRhs.t);
}

uchar4 operator*(uchar aLhs, const uchar4& aRhs) {
	return aRhs * aLhs;
}
