#pragma once
#ifndef GEODESUKA_CORE_MATH_CHAR3_H
#define GEODESUKA_CORE_MATH_CHAR3_H

#include "../config.h"

#include "../number/type.h"

union char3 {
	struct {
		char x, y, z;
	};
	struct {
		char r, g, b;
	};
	char ptr[3];

	char3() : x(0u), y(0u), z(0u) {}
	char3(char A) : x(A), y(A), z(A) {}
	char3(char X, char Y, char Z) : x(X), y(Y), z(Z) {}

	// Vector Space Stuff.
	char3& operator=(char aRhs);
	//char3& operator=(const char3& aRhs);
	//char3& operator=(char3&& aRhs) noexcept;

	// Access
	char operator[](int aIndex) const;
	char& operator[](int aIndex);

	// Vector addition and subtraction.
	char3 operator-() const;
	char3 operator+(char aRhs) const;
	char3 operator+(const char3& aRhs) const;
	char3 operator-(char aRhs) const;
	char3 operator-(const char3& aRhs) const;
	char3& operator+=(char aRhs);
	char3& operator+=(const char3& aRhs);
	char3& operator-=(char aRhs);
	char3& operator-=(const char3& aRhs);

	// Scalar multiplication & division.
	char3 operator*(char aRhs) const;
	char3 operator/(char aRhs) const;
	char3& operator*=(char aRhs);
	char3& operator/=(char aRhs);


	// Dot Product
	char operator*(const char3& aRhs) const;
	// Cross Product (Only exists in 3D)
	char3 operator^(const char3& aRhs) const;

};

char3 operator+(char aLhs, const char3& aRhs);
char3 operator-(char aLhs, const char3& aRhs);
char3 operator*(char aLhs, const char3& aRhs);

#endif // !GEODESUKA_CORE_MATH_CHAR3_H
