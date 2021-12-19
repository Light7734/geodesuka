#include <geodesuka/core/math/vector/ubyte3.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

ubyte3& ubyte3::operator=(ubyte aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	return *this;
}

ubyte3& ubyte3::operator=(const ubyte3& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	return *this;
}

ubyte3& ubyte3::operator=(ubyte3&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	return *this;
}

ubyte ubyte3::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

ubyte& ubyte3::operator[](int aIndex) {
	return this->ptr[aIndex];
}

ubyte3 ubyte3::operator+(ubyte aRhs) const {
	return ubyte3(this->x + aRhs, this->y + aRhs, this->z + aRhs);
}

ubyte3 ubyte3::operator+(const ubyte3& aRhs) const {
	return ubyte3(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z);
}

ubyte3 ubyte3::operator-(ubyte aRhs) const {
	return ubyte3(this->x - aRhs, this->y - aRhs, this->z - aRhs);
}

ubyte3 ubyte3::operator-(const ubyte3& aRhs) const {
	return ubyte3(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z);
}

ubyte3& ubyte3::operator+=(ubyte aRhs) {
	*this = *this + aRhs;
	return *this;
}

ubyte3& ubyte3::operator+=(const ubyte3& aRhs) {
	*this = *this + aRhs;
	return *this;
}

ubyte3& ubyte3::operator-=(ubyte aRhs) {
	*this = *this - aRhs;
	return *this;
}

ubyte3& ubyte3::operator-=(const ubyte3& aRhs) {
	*this = *this - aRhs;
	return *this;
}

ubyte3 ubyte3::operator*(ubyte aRhs) const {
	return ubyte3(this->x * aRhs, this->y * aRhs, this->z * aRhs);
}

ubyte3 ubyte3::operator/(ubyte aRhs) const {
	return ubyte3(this->x / aRhs, this->y / aRhs, this->z / aRhs);
}

ubyte3& ubyte3::operator*=(ubyte aRhs) {
	*this = *this * aRhs;
	return *this;
}

ubyte3& ubyte3::operator/=(ubyte aRhs) {
	*this = *this / aRhs;
	return *this;
}

ubyte ubyte3::operator*(const ubyte3& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z);
}

ubyte3 operator+(ubyte aLhs, const ubyte3& aRhs) {
	return aRhs + aLhs;
}

ubyte3 operator-(ubyte aLhs, const ubyte3& aRhs) {
	return ubyte3(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z);
}

ubyte3 operator*(ubyte aLhs, const ubyte3& aRhs) {
	return aRhs * aLhs;
}
