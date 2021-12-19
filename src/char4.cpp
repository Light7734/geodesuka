#include <geodesuka/core/math/vector/char4.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

char4& char4::operator=(char aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	this->t = aRhs;
	return *this;
}

char4& char4::operator=(const char4& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	this->t = aRhs.t;
	return *this;
}

char4& char4::operator=(char4&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	this->t = aRhs.t;
	return *this;
}

char char4::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

char& char4::operator[](int aIndex) {
	return this->ptr[aIndex];
}

char4 char4::operator-() const {
	return char4(-this->x, -this->y, -this->z, -this->t);
}

char4 char4::operator+(char aRhs) const {
	return char4(this->x + aRhs, this->y + aRhs, this->z + aRhs, this->t + aRhs);
}

char4 char4::operator+(const char4& aRhs) const {
	return char4(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z, this->t + aRhs.t);
}

char4 char4::operator-(char aRhs) const {
	return char4(this->x - aRhs, this->y - aRhs, this->z - aRhs, this->t - aRhs);
}

char4 char4::operator-(const char4& aRhs) const {
	return char4(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z, this->t - aRhs.t);
}

char4& char4::operator+=(char aRhs) {
	*this = *this + aRhs;
	return *this;
}

char4& char4::operator+=(const char4& aRhs) {
	*this = *this + aRhs;
	return *this;
}

char4& char4::operator-=(char aRhs) {
	*this = *this - aRhs;
	return *this;
}

char4& char4::operator-=(const char4& aRhs) {
	*this = *this - aRhs;
	return *this;
}

char4 char4::operator*(char aRhs) const {
	return char4(this->x * aRhs, this->y * aRhs, this->z * aRhs, this->t * aRhs);
}

char4 char4::operator/(char aRhs) const {
	return char4(this->x / aRhs, this->y / aRhs, this->z / aRhs, this->t / aRhs);
}

char4& char4::operator*=(char aRhs) {
	*this = *this * aRhs;
	return *this;
}

char4& char4::operator/=(char aRhs) {
	*this = *this / aRhs;
	return *this;
}

char char4::operator*(const char4& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z + this->t * aRhs.t);
}

char4 operator+(char aLhs, const char4& aRhs) {
	return aRhs + aLhs;
}

char4 operator-(char aLhs, const char4& aRhs) {
	return char4(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z, aLhs - aRhs.t);
}

char4 operator*(char aLhs, const char4& aRhs) {
	return aRhs * aLhs;
}

