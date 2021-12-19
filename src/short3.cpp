#include <geodesuka/core/math/vector/short3.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

short3& short3::operator=(short aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	return *this;
}

short3& short3::operator=(const short3& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	return *this;
}

short3& short3::operator=(short3&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	return *this;
}

short short3::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

short& short3::operator[](int aIndex) {
	return this->ptr[aIndex];
}

short3 short3::operator-() const {
	return short3(-this->x, -this->y, -this->z);
}

short3 short3::operator+(short aRhs) const {
	return short3(this->x + aRhs, this->y + aRhs, this->z + aRhs);
}

short3 short3::operator+(const short3& aRhs) const {
	return short3(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z);
}

short3 short3::operator-(short aRhs) const {
	return short3(this->x - aRhs, this->y - aRhs, this->z - aRhs);
}

short3 short3::operator-(const short3& aRhs) const {
	return short3(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z);
}

short3& short3::operator+=(short aRhs) {
	*this = *this + aRhs;
	return *this;
}

short3& short3::operator+=(const short3& aRhs) {
	*this = *this + aRhs;
	return *this;
}

short3& short3::operator-=(short aRhs) {
	*this = *this - aRhs;
	return *this;
}

short3& short3::operator-=(const short3& aRhs) {
	*this = *this - aRhs;
	return *this;
}

short3 short3::operator*(short aRhs) const {
	return short3(this->x * aRhs, this->y * aRhs, this->z * aRhs);
}

short3 short3::operator/(short aRhs) const {
	return short3(this->x / aRhs, this->y / aRhs, this->z / aRhs);
}

short3& short3::operator*=(short aRhs) {
	*this = *this * aRhs;
	return *this;
}

short3& short3::operator/=(short aRhs) {
	*this = *this / aRhs;
	return *this;
}

short short3::operator*(const short3& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z);
}

short3 short3::operator^(const short3& aRhs) const {
	return short3(
		this->y * aRhs.z - this->z * aRhs.y,
		this->z * aRhs.x - this->x * aRhs.z,
		this->x * aRhs.y - this->y * aRhs.x
	);
}

short3 operator+(short aLhs, const short3& aRhs) {
	return aRhs + aLhs;
}

short3 operator-(short aLhs, const short3& aRhs) {
	return short3(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z);
}

short3 operator*(short aLhs, const short3& aRhs) {
	return aRhs * aLhs;
}
