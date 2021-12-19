#pragma once
#ifndef GEODESUKA_CORE_MATH_INT3_H
#define GEODESUKA_CORE_MATH_INT3_H

#include "../config.h"

#include "../number/type.h"

union int3 {
	struct {
		int x, y, z;
	};
	struct {
		int r, g, b;
	};
	int ptr[3];

	int3() : x(0u), y(0u), z(0u) {}
	int3(int A) : x(A), y(A), z(A) {}
	int3(int X, int Y, int Z) : x(X), y(Y), z(Z) {}

	// Vector Space Stuff.
	int3& operator=(int aRhs);
	int3& operator=(const int3& aRhs);
	int3& operator=(int3&& aRhs) noexcept;

	// Access
	int operator[](int aIndex) const;
	int& operator[](int aIndex);

	// Vector addition and subtraction.
	int3 operator-() const;
	int3 operator+(int aRhs) const;
	int3 operator+(const int3& aRhs) const;
	int3 operator-(int aRhs) const;
	int3 operator-(const int3& aRhs) const;
	int3& operator+=(int aRhs);
	int3& operator+=(const int3& aRhs);
	int3& operator-=(int aRhs);
	int3& operator-=(const int3& aRhs);

	// Scalar multiplication & division.
	int3 operator*(int aRhs) const;
	int3 operator/(int aRhs) const;
	int3& operator*=(int aRhs);
	int3& operator/=(int aRhs);


	// Dot Product
	int	operator*(const int3& aRhs) const;
	// Cross Product (Only exists in 3D)
	int3 operator^(const int3& aRhs) const;

};

int3 operator+(int aLhs, const int3& aRhs);
int3 operator-(int aLhs, const int3& aRhs);
int3 operator*(int aLhs, const int3& aRhs);

#endif // !GEODESUKA_CORE_MATH_INT3_H
