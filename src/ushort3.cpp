#include <geodesuka/core/math/vector/ushort3.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

ushort3& ushort3::operator=(ushort aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	return *this;
}

//ushort3& ushort3::operator=(const ushort3& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	return *this;
//}
//
//ushort3& ushort3::operator=(ushort3&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	return *this;
//}

ushort ushort3::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

ushort& ushort3::operator[](int aIndex) {
	return this->ptr[aIndex];
}

ushort3 ushort3::operator+(ushort aRhs) const {
	return ushort3(this->x + aRhs, this->y + aRhs, this->z + aRhs);
}

ushort3 ushort3::operator+(const ushort3& aRhs) const {
	return ushort3(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z);
}

ushort3 ushort3::operator-(ushort aRhs) const {
	return ushort3(this->x - aRhs, this->y - aRhs, this->z - aRhs);
}

ushort3 ushort3::operator-(const ushort3& aRhs) const {
	return ushort3(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z);
}

ushort3& ushort3::operator+=(ushort aRhs) {
	*this = *this + aRhs;
	return *this;
}

ushort3& ushort3::operator+=(const ushort3& aRhs) {
	*this = *this + aRhs;
	return *this;
}

ushort3& ushort3::operator-=(ushort aRhs) {
	*this = *this - aRhs;
	return *this;
}

ushort3& ushort3::operator-=(const ushort3& aRhs) {
	*this = *this - aRhs;
	return *this;
}

ushort3 ushort3::operator*(ushort aRhs) const {
	return ushort3(this->x * aRhs, this->y * aRhs, this->z * aRhs);
}

ushort3 ushort3::operator/(ushort aRhs) const {
	return ushort3(this->x / aRhs, this->y / aRhs, this->z / aRhs);
}

ushort3& ushort3::operator*=(ushort aRhs) {
	*this = *this * aRhs;
	return *this;
}

ushort3& ushort3::operator/=(ushort aRhs) {
	*this = *this / aRhs;
	return *this;
}

ushort ushort3::operator*(const ushort3& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z);
}

ushort3 operator+(ushort aLhs, const ushort3& aRhs) {
	return aRhs + aLhs;
}

ushort3 operator-(ushort aLhs, const ushort3& aRhs) {
	return ushort3(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z);
}

ushort3 operator*(ushort aLhs, const ushort3& aRhs) {
	return aRhs * aLhs;
}

