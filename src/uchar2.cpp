#include <geodesuka/core/math/vector/uchar2.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

uchar2& uchar2::operator=(uchar aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	return *this;
}

//uchar2& uchar2::operator=(const uchar2& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	return *this;
//}
//
//uchar2& uchar2::operator=(uchar2&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	return *this;
//}

uchar uchar2::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

uchar& uchar2::operator[](int aIndex) {
	return this->ptr[aIndex];
}

uchar2 uchar2::operator+(uchar aRhs) const {
	return uchar2(this->x + aRhs, this->y + aRhs);
}

uchar2 uchar2::operator+(const uchar2& aRhs) const {
	return uchar2(this->x + aRhs.x, this->y + aRhs.y);
}

uchar2 uchar2::operator-(uchar aRhs) const {
	return uchar2(this->x - aRhs, this->y - aRhs);
}

uchar2 uchar2::operator-(const uchar2& aRhs) const {
	return uchar2(this->x - aRhs.x, this->y - aRhs.y);
}

uchar2& uchar2::operator+=(uchar aRhs) {
	*this = *this + aRhs;
	return *this;
}

uchar2& uchar2::operator+=(const uchar2& aRhs) {
	*this = *this + aRhs;
	return *this;
}

uchar2& uchar2::operator-=(uchar aRhs) {
	*this = *this - aRhs;
	return *this;
}

uchar2& uchar2::operator-=(const uchar2& aRhs) {
	*this = *this - aRhs;
	return *this;
}

uchar2 uchar2::operator*(uchar aRhs) const {
	return uchar2(this->x * aRhs, this->y * aRhs);
}

uchar2 uchar2::operator/(uchar aRhs) const {
	return uchar2(this->x / aRhs, this->y / aRhs);
}

uchar2& uchar2::operator*=(uchar aRhs) {
	*this = *this * aRhs;
	return *this;
}

uchar2& uchar2::operator/=(uchar aRhs) {
	*this = *this / aRhs;
	return *this;
}

uchar uchar2::operator*(const uchar2& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y);
}

uchar2 operator+(uchar aLhs, const uchar2& aRhs) {
	return aRhs + aLhs;
}

uchar2 operator-(uchar aLhs, const uchar2& aRhs) {
	return uchar2(aLhs - aRhs.x, aLhs - aRhs.y);
}

uchar2 operator*(uchar aLhs, const uchar2& aRhs) {
	return aRhs * aLhs;
}
