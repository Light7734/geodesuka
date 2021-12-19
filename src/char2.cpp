#include <geodesuka/core/math/vector/char2.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

char2& char2::operator=(char aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	return *this;
}

char2& char2::operator=(const char2& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

char2& char2::operator=(char2&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

char char2::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

char& char2::operator[](int aIndex) {
	return this->ptr[aIndex];
}

char2 char2::operator-() const {
	return char2(-this->x, -this->y);
}

char2 char2::operator+(char aRhs) const {
	return char2(this->x + aRhs, this->y + aRhs);
}

char2 char2::operator+(const char2& aRhs) const {
	return char2(this->x + aRhs.x, this->y + aRhs.y);
}

char2 char2::operator-(char aRhs) const {
	return char2(this->x - aRhs, this->y - aRhs);
}

char2 char2::operator-(const char2& aRhs) const {
	return char2(this->x - aRhs.x, this->y - aRhs.y);
}

char2& char2::operator+=(char aRhs) {
	*this = *this + aRhs;
	return *this;
}

char2& char2::operator+=(const char2& aRhs) {
	*this = *this + aRhs;
	return *this;
}

char2& char2::operator-=(char aRhs) {
	*this = *this - aRhs;
	return *this;
}

char2& char2::operator-=(const char2& aRhs) {
	*this = *this - aRhs;
	return *this;
}

char2 char2::operator*(char aRhs) const {
	return char2(this->x * aRhs, this->y * aRhs);
}

char2 char2::operator/(char aRhs) const {
	return char2(this->x / aRhs, this->y / aRhs);
}

char2& char2::operator*=(char aRhs) {
	*this = *this * aRhs;
	return *this;
}

char2& char2::operator/=(char aRhs) {
	*this = *this / aRhs;
	return *this;
}

char char2::operator*(const char2& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y);
}

char2 char2::operator^(const char2& aRhs) const {
	return (this->x * aRhs.y - this->y * aRhs.x);
}

char2 operator+(char aLhs, const char2& aRhs) {
	return aRhs + aLhs;
}

char2 operator-(char aLhs, const char2& aRhs) {
	return char2(aLhs - aRhs.x, aLhs - aRhs.y);
}

char2 operator*(char aLhs, const char2& aRhs) {
	return aRhs * aLhs;
}
