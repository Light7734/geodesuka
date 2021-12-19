#include <geodesuka/core/math/vector/short2.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

short2& short2::operator=(short aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	return *this;
}

short2& short2::operator=(const short2& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

short2& short2::operator=(short2&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

short short2::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

short& short2::operator[](int aIndex) {
	return this->ptr[aIndex];
}

short2 short2::operator-() const {
	return short2(-this->x, -this->y);
}

short2 short2::operator+(short aRhs) const {
	return short2(this->x + aRhs, this->y + aRhs);
}

short2 short2::operator+(const short2& aRhs) const {
	return short2(this->x + aRhs.x, this->y + aRhs.y);
}

short2 short2::operator-(short aRhs) const {
	return short2(this->x - aRhs, this->y - aRhs);
}

short2 short2::operator-(const short2& aRhs) const {
	return short2(this->x - aRhs.x, this->y - aRhs.y);
}

short2& short2::operator+=(short aRhs) {
	*this = *this + aRhs;
	return *this;
}

short2& short2::operator+=(const short2& aRhs) {
	*this = *this + aRhs;
	return *this;
}

short2& short2::operator-=(short aRhs) {
	*this = *this - aRhs;
	return *this;
}

short2& short2::operator-=(const short2& aRhs) {
	*this = *this - aRhs;
	return *this;
}

short2 short2::operator*(short aRhs) const {
	return short2(this->x * aRhs, this->y * aRhs);
}

short2 short2::operator/(short aRhs) const {
	return short2(this->x / aRhs, this->y / aRhs);
}

short2& short2::operator*=(short aRhs) {
	*this = *this * aRhs;
	return *this;
}

short2& short2::operator/=(short aRhs) {
	*this = *this / aRhs;
	return *this;
}

short short2::operator*(const short2& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y);
}

short short2::operator^(const short2& aRhs) const {
	return (this->x * aRhs.y - this->y * aRhs.x);
}

short2 operator+(short aLhs, const short2& aRhs) {
	return aRhs + aLhs;
}

short2 operator-(short aLhs, const short2& aRhs) {
	return short2(aLhs - aRhs.x, aLhs - aRhs.y);
}

short2 operator*(short aLhs, const short2& aRhs) {
	return aRhs * aLhs;
}

