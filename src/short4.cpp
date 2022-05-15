#include <geodesuka/core/math/vector/short4.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

short4& short4::operator=(short aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	this->t = aRhs;
	return *this;
}

//short4& short4::operator=(const short4& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	this->t = aRhs.t;
//	return *this;
//}
//
//short4& short4::operator=(short4&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	this->t = aRhs.t;
//	return *this;
//}

short short4::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

short& short4::operator[](int aIndex) {
	return this->ptr[aIndex];
}

short4 short4::operator-() const {
	return short4(-this->x, -this->y, -this->z, -this->t);
}

short4 short4::operator+(short aRhs) const {
	return short4(this->x + aRhs, this->y + aRhs, this->z + aRhs, this->t + aRhs);
}

short4 short4::operator+(const short4& aRhs) const {
	return short4(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z, this->t + aRhs.t);
}

short4 short4::operator-(short aRhs) const {
	return short4(this->x - aRhs, this->y - aRhs, this->z - aRhs, this->t - aRhs);
}

short4 short4::operator-(const short4& aRhs) const {
	return short4(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z, this->t - aRhs.t);
}

short4& short4::operator+=(short aRhs) {
	*this = *this + aRhs;
	return *this;
}

short4& short4::operator+=(const short4& aRhs) {
	*this = *this + aRhs;
	return *this;
}

short4& short4::operator-=(short aRhs) {
	*this = *this - aRhs;
	return *this;
}

short4& short4::operator-=(const short4& aRhs) {
	*this = *this - aRhs;
	return *this;
}

short4 short4::operator*(short aRhs) const {
	return short4(this->x * aRhs, this->y * aRhs, this->z * aRhs, this->t * aRhs);
}

short4 short4::operator/(short aRhs) const {
	return short4(this->x / aRhs, this->y / aRhs, this->z / aRhs, this->t / aRhs);
}

short4& short4::operator*=(short aRhs) {
	*this = *this * aRhs;
	return *this;
}

short4& short4::operator/=(short aRhs) {
	*this = *this / aRhs;
	return *this;
}

short short4::operator*(const short4& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z + this->t * aRhs.t);
}

short4 operator+(short aLhs, const short4& aRhs) {
	return aRhs + aLhs;
}

short4 operator-(short aLhs, const short4& aRhs) {
	return short4(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z, aLhs - aRhs.t);
}

short4 operator*(short aLhs, const short4& aRhs) {
	return aRhs * aLhs;
}

