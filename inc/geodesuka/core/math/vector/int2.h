#pragma once
#ifndef GEODESUKA_CORE_MATH_INT2_H
#define GEODESUKA_CORE_MATH_INT2_H

#include "../config.h"

#include "../number/type.h"

union int2 {
	struct {
		int x, y;
	};
	struct {
		int r, g;
	};
	int ptr[2];

	int2() : x(0u), y(0u) {}
	int2(int A) : x(A), y(A) {}
	int2(int X, int Y) : x(X), y(Y) {}

	// Vector Space Stuff.
	int2& operator=(int aRhs);
	//int2& operator=(int2 aRhs);
	//int2& operator=(const int2& aRhs);
	//int2& operator=(int2&& aRhs) noexcept;

	// Access
	int operator[](int aIndex) const;
	int& operator[](int aIndex);

	// Vector addition and subtraction.
	int2 operator-() const;
	int2 operator+(int aRhs) const;
	int2 operator+(const int2& aRhs) const;
	int2 operator-(int aRhs) const;
	int2 operator-(const int2& aRhs) const;
	int2& operator+=(int aRhs);
	int2& operator+=(const int2& aRhs);
	int2& operator-=(int aRhs);
	int2& operator-=(const int2& aRhs);

	// Scalar multiplication & division.
	int2 operator*(int aRhs) const;
	int2 operator/(int aRhs) const;
	int2& operator*=(int aRhs);
	int2& operator/=(int aRhs);


	// Dot Product
	int	operator*(const int2& aRhs) const;
	// Cross Product (Only exists in 3D)
	int operator^(const int2& aRhs) const;

};

int2 operator+(int aLhs, const int2& aRhs);
int2 operator-(int aLhs, const int2& aRhs);
int2 operator*(int aLhs, const int2& aRhs);

#endif // !GEODESUKA_CORE_MATH_INT2_H
