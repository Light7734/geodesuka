#include <geodesuka/core/math/vector/ushort4.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

ushort4& ushort4::operator=(ushort aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	this->t = aRhs;
	return *this;
}

//ushort4& ushort4::operator=(const ushort4& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	this->t = aRhs.t;
//	return *this;
//}
//
//ushort4& ushort4::operator=(ushort4&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	this->t = aRhs.t;
//	return *this;
//}

ushort ushort4::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

ushort& ushort4::operator[](int aIndex) {
	return this->ptr[aIndex];
}

ushort4 ushort4::operator+(ushort aRhs) const {
	return ushort4(this->x + aRhs, this->y + aRhs, this->z + aRhs, this->t + aRhs);
}

ushort4 ushort4::operator+(const ushort4& aRhs) const {
	return ushort4(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z, this->t + aRhs.t);
}

ushort4 ushort4::operator-(ushort aRhs) const {
	return ushort4(this->x - aRhs, this->y - aRhs, this->z - aRhs, this->t - aRhs);
}

ushort4 ushort4::operator-(const ushort4& aRhs) const {
	return ushort4(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z, this->t - aRhs.t);
}

ushort4& ushort4::operator+=(ushort aRhs) {
	*this = *this + aRhs;
	return *this;
}

ushort4& ushort4::operator+=(const ushort4& aRhs) {
	*this = *this + aRhs;
	return *this;
}

ushort4& ushort4::operator-=(ushort aRhs) {
	*this = *this - aRhs;
	return *this;
}

ushort4& ushort4::operator-=(const ushort4& aRhs) {
	*this = *this - aRhs;
	return *this;
}

ushort4 ushort4::operator*(ushort aRhs) const {
	return ushort4(this->x * aRhs, this->y * aRhs, this->z * aRhs, this->t * aRhs);
}

ushort4 ushort4::operator/(ushort aRhs) const {
	return ushort4(this->x / aRhs, this->y / aRhs, this->z / aRhs, this->t / aRhs);
}

ushort4& ushort4::operator*=(ushort aRhs) {
	*this = *this * aRhs;
	return *this;
}

ushort4& ushort4::operator/=(ushort aRhs) {
	*this = *this / aRhs;
	return *this;
}

ushort ushort4::operator*(const ushort4& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z + this->t * aRhs.t);
}

ushort4 operator+(ushort aLhs, const ushort4& aRhs) {
	return aRhs + aLhs;
}

ushort4 operator-(ushort aLhs, const ushort4& aRhs) {
	return ushort4(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z, aLhs - aRhs.t);
}

ushort4 operator*(ushort aLhs, const ushort4& aRhs) {
	return aRhs * aLhs;
}
