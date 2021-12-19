#include <geodesuka/core/math/vector/ubyte4.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

ubyte4& ubyte4::operator=(ubyte aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	this->t = aRhs;
	return *this;
}

ubyte4& ubyte4::operator=(const ubyte4& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	this->t = aRhs.t;
	return *this;
}

ubyte4& ubyte4::operator=(ubyte4&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	this->t = aRhs.t;
	return *this;
}

ubyte ubyte4::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

ubyte& ubyte4::operator[](int aIndex) {
	return this->ptr[aIndex];
}

ubyte4 ubyte4::operator+(ubyte aRhs) const {
	return ubyte4(this->x + aRhs, this->y + aRhs, this->z + aRhs, this->t + aRhs);
}

ubyte4 ubyte4::operator+(const ubyte4& aRhs) const {
	return ubyte4(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z, this->t + aRhs.t);
}

ubyte4 ubyte4::operator-(ubyte aRhs) const {
	return ubyte4(this->x - aRhs, this->y - aRhs, this->z - aRhs, this->t - aRhs);
}

ubyte4 ubyte4::operator-(const ubyte4& aRhs) const {
	return ubyte4(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z, this->t - aRhs.t);
}

ubyte4& ubyte4::operator+=(ubyte aRhs) {
	*this = *this + aRhs;
	return *this;
}

ubyte4& ubyte4::operator+=(const ubyte4& aRhs) {
	*this = *this + aRhs;
	return *this;
}

ubyte4& ubyte4::operator-=(ubyte aRhs) {
	*this = *this - aRhs;
	return *this;
}

ubyte4& ubyte4::operator-=(const ubyte4& aRhs) {
	*this = *this - aRhs;
	return *this;
}

ubyte4 ubyte4::operator*(ubyte aRhs) const {
	return ubyte4(this->x * aRhs, this->y * aRhs, this->z * aRhs, this->t * aRhs);
}

ubyte4 ubyte4::operator/(ubyte aRhs) const {
	return ubyte4(this->x / aRhs, this->y / aRhs, this->z / aRhs, this->t / aRhs);
}

ubyte4& ubyte4::operator*=(ubyte aRhs) {
	*this = *this * aRhs;
	return *this;
}

ubyte4& ubyte4::operator/=(ubyte aRhs) {
	*this = *this / aRhs;
	return *this;
}

ubyte ubyte4::operator*(const ubyte4& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z + this->t * aRhs.t);
}

ubyte4 operator+(ubyte aLhs, const ubyte4& aRhs) {
	return aRhs + aLhs;
}

ubyte4 operator-(ubyte aLhs, const ubyte4& aRhs) {
	return ubyte4(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z, aLhs - aRhs.t);
}

ubyte4 operator*(ubyte aLhs, const ubyte4& aRhs) {
	return aRhs * aLhs;
}
