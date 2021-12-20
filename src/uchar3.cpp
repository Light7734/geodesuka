#include <geodesuka/core/math/vector/uchar3.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

uchar3& uchar3::operator=(uchar aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	return *this;
}

//uchar3& uchar3::operator=(const uchar3& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	return *this;
//}
//
//uchar3& uchar3::operator=(uchar3&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	return *this;
//}

uchar uchar3::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

uchar& uchar3::operator[](int aIndex) {
	return this->ptr[aIndex];
}

uchar3 uchar3::operator+(uchar aRhs) const {
	return uchar3(this->x + aRhs, this->y + aRhs, this->z + aRhs);
}

uchar3 uchar3::operator+(const uchar3& aRhs) const {
	return uchar3(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z);
}

uchar3 uchar3::operator-(uchar aRhs) const {
	return uchar3(this->x - aRhs, this->y - aRhs, this->z - aRhs);
}

uchar3 uchar3::operator-(const uchar3& aRhs) const {
	return uchar3(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z);
}

uchar3& uchar3::operator+=(uchar aRhs) {
	*this = *this + aRhs;
	return *this;
}

uchar3& uchar3::operator+=(const uchar3& aRhs) {
	*this = *this + aRhs;
	return *this;
}

uchar3& uchar3::operator-=(uchar aRhs) {
	*this = *this - aRhs;
	return *this;
}

uchar3& uchar3::operator-=(const uchar3& aRhs) {
	*this = *this - aRhs;
	return *this;
}

uchar3 uchar3::operator*(uchar aRhs) const {
	return uchar3(this->x * aRhs, this->y * aRhs, this->z * aRhs);
}

uchar3 uchar3::operator/(uchar aRhs) const {
	return uchar3(this->x / aRhs, this->y / aRhs, this->z / aRhs);
}

uchar3& uchar3::operator*=(uchar aRhs) {
	*this = *this * aRhs;
	return *this;
}

uchar3& uchar3::operator/=(uchar aRhs) {
	*this = *this / aRhs;
	return *this;
}

uchar uchar3::operator*(const uchar3& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z);
}

uchar3 operator+(uchar aLhs, const uchar3& aRhs) {
	return aRhs + aLhs;
}

uchar3 operator-(uchar aLhs, const uchar3& aRhs) {
	return uchar3(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z);
}

uchar3 operator*(uchar aLhs, const uchar3& aRhs) {
	return aRhs * aLhs;
}
