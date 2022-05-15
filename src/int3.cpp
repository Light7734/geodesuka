#include <geodesuka/core/math/vector/int3.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

int3& int3::operator=(int aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	this->z = aRhs;
	return *this;
}

//int3& int3::operator=(const int3& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	return *this;
//}
//
//int3& int3::operator=(int3&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	this->z = aRhs.z;
//	return *this;
//}

int int3::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

int& int3::operator[](int aIndex) {
	return this->ptr[aIndex];
}

int3 int3::operator-() const {
	return int3(-this->x, -this->y, -this->z);
}

int3 int3::operator+(int aRhs) const {
	return int3(this->x + aRhs, this->y + aRhs, this->z + aRhs);
}

int3 int3::operator+(const int3& aRhs) const {
	return int3(this->x + aRhs.x, this->y + aRhs.y, this->z + aRhs.z);
}

int3 int3::operator-(int aRhs) const {
	return int3(this->x - aRhs, this->y - aRhs, this->z - aRhs);
}

int3 int3::operator-(const int3& aRhs) const {
	return int3(this->x - aRhs.x, this->y - aRhs.y, this->z - aRhs.z);
}

int3& int3::operator+=(int aRhs) {
	*this = *this + aRhs;
	return *this;
}

int3& int3::operator+=(const int3& aRhs) {
	*this = *this + aRhs;
	return *this;
}

int3& int3::operator-=(int aRhs) {
	*this = *this - aRhs;
	return *this;
}

int3& int3::operator-=(const int3& aRhs) {
	*this = *this - aRhs;
	return *this;
}

int3 int3::operator*(int aRhs) const {
	return int3(this->x * aRhs, this->y * aRhs, this->z * aRhs);
}

int3 int3::operator/(int aRhs) const {
	return int3(this->x / aRhs, this->y / aRhs, this->z / aRhs);
}

int3& int3::operator*=(int aRhs) {
	*this = *this * aRhs;
	return *this;
}

int3& int3::operator/=(int aRhs) {
	*this = *this / aRhs;
	return *this;
}

int int3::operator*(const int3& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y + this->z * aRhs.z);
}

int3 int3::operator^(const int3& aRhs) const {
	return int3(
		this->y * aRhs.z - this->z * aRhs.y,
		this->z * aRhs.x - this->x * aRhs.z,
		this->x * aRhs.y - this->y * aRhs.x
	);
}

int3 operator+(int aLhs, const int3& aRhs) {
	return aRhs + aLhs;
}

int3 operator-(int aLhs, const int3& aRhs) {
	return int3(aLhs - aRhs.x, aLhs - aRhs.y, aLhs - aRhs.z);
}

int3 operator*(int aLhs, const int3& aRhs) {
	return aRhs * aLhs;
}

