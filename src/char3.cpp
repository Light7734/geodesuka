#include <geodesuka/core/math/vector/char3.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

char3& char3::operator=(char aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	return *this;
}

char3& char3::operator=(const char3& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	return *this;
}

char3& char3::operator=(char3&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	this->z = aRhs.z;
	return *this;
}

char char3::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

char& char3::operator[](int aIndex) {
	return this->ptr[aIndex];
}

char3 char3::operator-() const {
	return char3(-this->x, -this->y, -this->z);
}

char3 char3::operator+(char aRhs) const {
	return char3(this->x + aRhs, this->y + aRhs, this->z + aRhs);
}

char3 char3::operator+(const char3& aRhs) const {
	return char3(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z);
}

char3 char3::operator-(char aRhs) const {
	return char3(this->x - aRhs, this->y - aRhs, this->z - aRhs);
}

char3 char3::operator-(const char3& aRhs) const {
	return char3(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z);
}

char3& char3::operator+=(char aRhs) {
	*this = *this + aRhs;
	return *this;
}

char3& char3::operator+=(const char3& aRhs) {
	*this = *this + aRhs;
	return *this;
}

char3& char3::operator-=(char aRhs) {
	*this = *this - aRhs;
	return *this;
}

char3& char3::operator-=(const char3& aRhs) {
	*this = *this - aRhs;
	return *this;
}

char3 char3::operator*(char aRhs) const {
	return char3(this->x * aRhs, this->y * aRhs, this->z * aRhs);
}

char3 char3::operator/(char aRhs) const {
	return char3(this->x / aRhs, this->y / aRhs, this->z / aRhs);
}

char3& char3::operator*=(char aRhs) {
	*this = *this * aRhs;
	return *this;
}

char3& char3::operator/=(char aRhs) {
	*this = *this / aRhs;
	return *this;
}

char char3::operator*(const char3& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z);
}

char3 char3::operator^(const char3& aRhs) const {
	return char3(
		this->y * aRhs.z - this->z * aRhs.y,
		this->z * aRhs.x - this->x * aRhs.z,
		this->x * aRhs.y - this->y * aRhs.x
	);
}

char3 operator+(char aLhs, const char3& aRhs) {
	return aRhs + aLhs;
}

char3 operator-(char aLhs, const char3& aRhs) {
	return char3(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z);
}

char3 operator*(char aLhs, const char3& aRhs) {
	return aRhs * aLhs;
}

