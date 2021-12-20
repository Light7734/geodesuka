#pragma once
#ifndef GEODESUKA_CORE_MATH_CHAR2_H
#define GEODESUKA_CORE_MATH_CHAR2_H

#include "../config.h"

#include "../number/type.h"

union char2 {
	struct {
		char x, y;
	};
	struct {
		char r, g;
	};
	char ptr[2];

	char2() : x(0u), y(0u) {}
	char2(char A) : x(A), y(A) {}
	char2(char X, char Y) : x(X), y(Y) {}

	// Vector Space Stuff.
	char2& operator=(char aRhs);
	//char2& operator=(const char2& aRhs);
	//char2& operator=(char2&& aRhs) noexcept;

	// Access
	char operator[](int aIndex) const;
	char& operator[](int aIndex);

	// Vector addition and subtraction.
	char2 operator-() const;
	char2 operator+(char aRhs) const;
	char2 operator+(const char2& aRhs) const;
	char2 operator-(char aRhs) const;
	char2 operator-(const char2& aRhs) const;
	char2& operator+=(char aRhs);
	char2& operator+=(const char2& aRhs);
	char2& operator-=(char aRhs);
	char2& operator-=(const char2& aRhs);

	// Scalar multiplication & division.
	char2 operator*(char aRhs) const;
	char2 operator/(char aRhs) const;
	char2& operator*=(char aRhs);
	char2& operator/=(char aRhs);


	// Dot Product
	char operator*(const char2& aRhs) const;
	// Cross Product (Only exists in 3D)
	char2 operator^(const char2& aRhs) const;

};

char2 operator+(char aLhs, const char2& aRhs);
char2 operator-(char aLhs, const char2& aRhs);
char2 operator*(char aLhs, const char2& aRhs);

#endif // !GEODESUKA_CORE_MATH_CHAR2_H
