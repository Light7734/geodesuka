#include <geodesuka/core/math/vector/int4.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

int4& int4::operator=(int aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	this->t = aRhs;
	return *this;
}

//int4& int4::operator=(const int4& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	this->t = aRhs.t;
//	return *this;
//}
//
//int4& int4::operator=(int4&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	this->t = aRhs.t;
//	return *this;
//}

int int4::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

int& int4::operator[](int aIndex) {
	return this->ptr[aIndex];
}

int4 int4::operator-() const {
	return int4(-this->x, -this->y, -this->z, -this->t);
}

int4 int4::operator+(int aRhs) const {
	return int4(this->x + aRhs, this->y + aRhs, this->z + aRhs, this->t + aRhs);
}

int4 int4::operator+(const int4& aRhs) const {
	return int4(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z, this->t + aRhs.t);
}

int4 int4::operator-(int aRhs) const {
	return int4(this->x - aRhs, this->y - aRhs, this->z - aRhs, this->t - aRhs);
}

int4 int4::operator-(const int4& aRhs) const {
	return int4(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z, this->t - aRhs.t);
}

int4& int4::operator+=(int aRhs) {
	*this = *this + aRhs;
	return *this;
}

int4& int4::operator+=(const int4& aRhs) {
	*this = *this + aRhs;
	return *this;
}

int4& int4::operator-=(int aRhs) {
	*this = *this - aRhs;
	return *this;
}

int4& int4::operator-=(const int4& aRhs) {
	*this = *this - aRhs;
	return *this;
}

int4 int4::operator*(int aRhs) const {
	return int4(this->x * aRhs, this->y * aRhs, this->z * aRhs, this->t * aRhs);
}

int4 int4::operator/(int aRhs) const {
	return int4(this->x / aRhs, this->y / aRhs, this->z / aRhs, this->t / aRhs);
}

int4& int4::operator*=(int aRhs) {
	*this = *this * aRhs;
	return *this;
}

int4& int4::operator/=(int aRhs) {
	*this = *this / aRhs;
	return *this;
}

int int4::operator*(const int4& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z + this->t * aRhs.t);
}

int4 operator+(int aLhs, const int4& aRhs) {
	return aRhs + aLhs;
}

int4 operator-(int aLhs, const int4& aRhs) {
	return int4(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z, aLhs - aRhs.t);
}

int4 operator*(int aLhs, const int4& aRhs) {
	return aRhs * aLhs;
}
