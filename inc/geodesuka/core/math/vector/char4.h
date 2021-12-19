#pragma once
#ifndef GEODESUKA_CORE_MATH_CHAR4_H
#define GEODESUKA_CORE_MATH_CHAR4_H

#include "../config.h"

#include "../number/type.h"

union char4 {
	struct {
		char x, y, z, t;
	};
	struct {
		char r, g, b, a;
	};
	char ptr[4];

	char4() : x(0u), y(0u), z(0u), t(0u) {}
	char4(char A) : x(A), y(A), z(A), t(A) {}
	char4(char X, char Y, char Z, char T) : x(X), y(Y), z(Z), t(T) {}

	// Vector Space Stuff.
	char4& operator=(char aRhs);
	char4& operator=(const char4& aRhs);
	char4& operator=(char4&& aRhs) noexcept;

	// Access
	char operator[](int aIndex) const;
	char& operator[](int aIndex);

	// Vector addition and subtraction.
	char4 operator-() const;
	char4 operator+(char aRhs) const;
	char4 operator+(const char4& aRhs) const;
	char4 operator-(char aRhs) const;
	char4 operator-(const char4& aRhs) const;
	char4& operator+=(char aRhs);
	char4& operator+=(const char4& aRhs);
	char4& operator-=(char aRhs);
	char4& operator-=(const char4& aRhs);

	// Scalar multiplication & division.
	char4 operator*(char aRhs) const;
	char4 operator/(char aRhs) const;
	char4& operator*=(char aRhs);
	char4& operator/=(char aRhs);


	// Dot Product
	char	operator*(const char4& aRhs) const;
	// Cross Product (Only exists in 3D)
	//char4	operator^(const char4& aRhs) const;

};

char4 operator+(char aLhs, const char4& aRhs);
char4 operator-(char aLhs, const char4& aRhs);
char4 operator*(char aLhs, const char4& aRhs);

#endif // !GEODESUKA_CORE_MATH_CHAR4_H
