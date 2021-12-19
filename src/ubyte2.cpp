#include <geodesuka/core/math/vector/ubyte2.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

ubyte2& ubyte2::operator=(ubyte aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	return *this;
}

ubyte2& ubyte2::operator=(const ubyte2& aRhs) {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

ubyte2& ubyte2::operator=(ubyte2&& aRhs) noexcept {
	this->x = aRhs.x;
	this->y = aRhs.y;
	return *this;
}

ubyte ubyte2::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

ubyte& ubyte2::operator[](int aIndex) {
	return this->ptr[aIndex];
}

ubyte2 ubyte2::operator+(ubyte aRhs) const {
	return ubyte2(this->x + aRhs, this->y + aRhs);
}

ubyte2 ubyte2::operator+(const ubyte2& aRhs) const {
	return ubyte2(this->x + aRhs.x, this->y + aRhs.y);
}

ubyte2 ubyte2::operator-(ubyte aRhs) const {
	return ubyte2(this->x - aRhs, this->y - aRhs);
}

ubyte2 ubyte2::operator-(const ubyte2& aRhs) const {
	return ubyte2(this->x - aRhs.x, this->y - aRhs.y);
}

ubyte2& ubyte2::operator+=(ubyte aRhs) {
	*this = *this + aRhs;
	return *this;
}

ubyte2& ubyte2::operator+=(const ubyte2& aRhs) {
	*this = *this + aRhs;
	return *this;
}

ubyte2& ubyte2::operator-=(ubyte aRhs) {
	*this = *this - aRhs;
	return *this;
}

ubyte2& ubyte2::operator-=(const ubyte2& aRhs) {
	*this = *this - aRhs;
	return *this;
}

ubyte2 ubyte2::operator*(ubyte aRhs) const {
	return ubyte2(this->x * aRhs, this->y * aRhs);
}

ubyte2 ubyte2::operator/(ubyte aRhs) const {
	return ubyte2(this->x / aRhs, this->y / aRhs);
}

ubyte2& ubyte2::operator*=(ubyte aRhs) {
	*this = *this * aRhs;
	return *this;
}

ubyte2& ubyte2::operator/=(ubyte aRhs) {
	*this = *this / aRhs;
	return *this;
}

ubyte ubyte2::operator*(const ubyte2& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y);
}

ubyte2 operator+(ubyte aLhs, const ubyte2& aRhs) {
	return aRhs + aLhs;
}

ubyte2 operator-(ubyte aLhs, const ubyte2& aRhs) {
	return ubyte2(aLhs - aRhs.x, aLhs - aRhs.y);
}

ubyte2 operator*(ubyte aLhs, const ubyte2& aRhs) {
	return aRhs * aLhs;
}
