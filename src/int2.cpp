#include <geodesuka/core/math/vector/int2.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>

//int int2::operator^(const int2& Rhs) const {
//	return (this->x * Rhs.y - this->y * Rhs.x);
//}

int2& int2::operator=(int aRhs) {
	this->x = aRhs;
	this->y = aRhs;
	return *this;
}

//int2& int2::operator=(const int2& aRhs) {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	return *this;
//}
//
//int2& int2::operator=(int2&& aRhs) noexcept {
//	this->x = aRhs.x;
//	this->y = aRhs.y;
//	return *this;
//}

int int2::operator[](int aIndex) const {
	return this->ptr[aIndex];
}

int& int2::operator[](int aIndex) {
	return this->ptr[aIndex];
}

int2 int2::operator-() const {
	return int2(-this->x, -this->y);
}

int2 int2::operator+(int aRhs) const {
	return int2(this->x + aRhs, this->y + aRhs);
}

int2 int2::operator+(const int2& aRhs) const {
	return int2(this->x + aRhs.x, this->y + aRhs.y);
}

int2 int2::operator-(int aRhs) const {
	return int2(this->x - aRhs, this->y - aRhs);
}

int2 int2::operator-(const int2& aRhs) const {
	return int2(this->x - aRhs.x, this->y - aRhs.y);
}

int2& int2::operator+=(int aRhs) {
	*this = *this + aRhs;
	return *this;
}

int2& int2::operator+=(const int2& aRhs) {
	*this = *this + aRhs;
	return *this;
}

int2& int2::operator-=(int aRhs) {
	*this = *this - aRhs;
	return *this;
}

int2& int2::operator-=(const int2& aRhs) {
	*this = *this - aRhs;
	return *this;
}

int2 int2::operator*(int aRhs) const {
	return int2(this->x * aRhs, this->y * aRhs);
}

int2 int2::operator/(int aRhs) const {
	return int2(this->x / aRhs, this->y / aRhs);
}

int2& int2::operator*=(int aRhs) {
	*this = *this * aRhs;
	return *this;
}

int2& int2::operator/=(int aRhs) {
	*this = *this / aRhs;
	return *this;
}

int int2::operator*(const int2& aRhs) const {
	return (this->x * aRhs.x + this->y * aRhs.y);
}

int int2::operator^(const int2& aRhs) const {
	return (this->x * aRhs.y - this->y * aRhs.x);
}

int2 operator+(int aLhs, const int2& aRhs) {
	return aRhs + aLhs;
}

int2 operator-(int aLhs, const int2& aRhs) {
	return int2(aLhs - aRhs.x, aLhs - aRhs.y);
}

int2 operator*(int aLhs, const int2& aRhs) {
	return aRhs * aLhs;
}






//int2 operator+(int2 lhs, int2 rhs) {
//	int2 temp = { lhs.x + rhs.x, lhs.y + rhs.y };
//	return temp;
//}
//
//int2 operator-(int2 lhs, int2 rhs) {
//	int2 temp = { lhs.x - rhs.x, lhs.y - rhs.y };
//	return temp;
//}
//
//int operator*(int2 lhs, int2 rhs) {
//	return (lhs.x * rhs.x + lhs.y * rhs.y);
//}
//
//int operator^(int2 lhs, int2 rhs) {
//	return (lhs.x*rhs.y - lhs.y*rhs.x);
//}
//
//int2 operator+(int lhs, int2 rhs) {
//	int2 temp = { lhs + rhs.x, lhs + rhs.y };
//	return temp;
//}
//
//int2 operator-(int lhs, int2 rhs) {
//	int2 temp = { lhs - rhs.x, lhs - rhs.y };
//	return temp;
//}
//
//int2 operator*(int lhs, int2 rhs) {
//	int2 temp = { lhs * rhs.x, lhs * rhs.y };
//	return temp;
//}
//
//int2 operator+(int2 lhs, int rhs) {
//	int2 temp = { lhs.x + rhs, lhs.y + rhs };
//	return temp;
//}
//
//int2 operator-(int2 lhs, int rhs) {
//	int2 temp = { lhs.x - rhs, lhs.y - rhs };
//	return temp;
//}
//
//int2 operator*(int2 lhs, int rhs) {
//	int2 temp = { lhs.x * rhs, lhs.y * rhs };
//	return temp;
//}
//
//int2 operator/(int2 lhs, int rhs) {
//	int2 temp;
//	if (rhs != 0) {
//		temp = { lhs.x / rhs, lhs.y / rhs };
//	}
//	else {
//		temp = { INT_MAX, INT_MAX };
//	}
//	return temp;
//}
//
//int2::int2() {
//	this->x = 0; this->y = 0;
//}
//
//int2::~int2() {}
//#ifdef CS_PLEB_NOTATION
//int2::int2(int Arg) {
//	this->x = Arg; this->y = Arg;
//}
//#endif // CS_PLEB_NOTATION
//
//int2::int2(int ArgX, int ArgY) {
//	this->x = ArgX; this->y = ArgY;
//}
//
//int2::int2(const int2& Arg) {
//	this->x = Arg.x; this->y = Arg.y;
//}
//#ifdef CS_PLEB_NOTATION
//int2& int2::operator=(int Rhs) {
//	this->x = Rhs; this->y = Rhs;
//	return *this;
//}
//#endif // CS_PLEB_NOTATION
//int2& int2::operator=(const int2& Rhs) {
//	this->x = Rhs.x; this->y = Rhs.y;
//	return *this;
//}
//
//int int2::operator[](int Index) const {
//	return this->ptr[Index];
//}
//
//int& int2::operator[](int Index) {
//	return this->ptr[Index];
//}
//
//int2 int2::operator-() const
//{
//	return int2(-this->x, -this->y);
//}
//
//int2 int2::operator+(const int2& Rhs) const {
//	return int2(this->x + Rhs.x, this->y + Rhs.y);
//}
//
//int2 int2::operator-(const int2& Rhs) const {
//	return int2(this->x - Rhs.x, this->y - Rhs.y);
//}
//
//int int2::operator*(const int2& Rhs) const {
//	return (this->x * Rhs.x + this->y * Rhs.y);
//}
//
//int int2::operator^(const int2& Rhs) const {
//	return (this->x * Rhs.y - this->y * Rhs.x);
//}
//
//int2& int2::operator+=(const int2& Rhs) {
//	*this = *this + Rhs;
//	return *this;
//}
//
//int2& int2::operator-=(const int2& Rhs) {
//	*this = *this - Rhs;
//	return *this;
//}
//#ifdef CS_PLEB_NOTATION
//int2 int2::operator+(int Rhs) const {
//	return int2(this->x + Rhs, this->y + Rhs);
//}
//
//int2 int2::operator-(int Rhs) const {
//	return int2(this->x - Rhs, this->y - Rhs);
//}
//#endif // CS_PLEB_NOTATION
//int2 int2::operator*(int Rhs) const {
//	return int2(this->x * Rhs, this->y * Rhs);
//}
//
//int2 int2::operator/(int Rhs) const
//{
//	return int2(this->x / Rhs, this->y / Rhs);
//}
//#ifdef CS_PLEB_NOTATION
//int2& int2::operator+=(int Rhs) {
//	*this = *this + Rhs;
//	return *this;
//}
//
//int2& int2::operator-=(int Rhs) {
//	*this = *this - Rhs;
//	return *this;
//}
//#endif // CS_PLEB_NOTATION
//int2& int2::operator*=(int Rhs) {
//	*this = *this * Rhs;
//	return *this;
//}
//
//int2& int2::operator/=(int Rhs) {
//	*this = *this / Rhs;
//	return *this;
//}
//#ifdef CS_PLEB_NOTATION
//int2 operator+(int Lhs, const int2& Rhs) {
//	return int2(Lhs + Rhs.x, Lhs + Rhs.y);
//}
//
//int2 operator-(int Lhs, const int2& Rhs) {
//	return int2(Lhs - Rhs.x, Lhs - Rhs.y);
//}
//#endif // CS_PLEB_NOTATION
//int2 operator*(int Lhs, const int2& Rhs) {
//	return int2(Lhs * Rhs.x, Lhs * Rhs.y);
//}
//#ifdef CS_PLEB_NOTATION
//int2 operator/(int Lhs, const int2& Rhs) {
//	return int2(Lhs / Rhs.x, Lhs / Rhs.y);
//}
//#endif // CS_PLEB_NOTATION
