#pragma once
#ifndef GEODESUKA_CORE_MATH_BYTE3_H
#define GEODESUKA_CORE_MATH_BYTE3_H

#include "../config.h"

#include "../number/type.h"

union byte3 {
	struct {
		byte x, y, z;
	};
	struct {
		byte r, g, b;
	};
	byte ptr[3];

	byte3() : x(0u), y(0u), z(0u) {}
	byte3(byte A) : x(A), y(A), z(A) {}
	byte3(byte X, byte Y, byte Z) : x(X), y(Y), z(Z) {}

	// Vector Space Stuff.
	byte3& operator=(byte aRhs);
	byte3& operator=(const byte3& aRhs);
	byte3& operator=(byte3&& aRhs) noexcept;

	// Access
	byte operator[](int aIndex) const;
	byte& operator[](int aIndex);

	// Vector addition and subtraction.
	byte3 operator-() const;
	byte3 operator+(byte aRhs) const;
	byte3 operator+(const byte3& aRhs) const;
	byte3 operator-(byte aRhs) const;
	byte3 operator-(const byte3& aRhs) const;
	byte3& operator+=(byte aRhs);
	byte3& operator+=(const byte3& aRhs);
	byte3& operator-=(byte aRhs);
	byte3& operator-=(const byte3& aRhs);

	// Scalar multiplication & division.
	byte3 operator*(byte aRhs) const;
	byte3 operator/(byte aRhs) const;
	byte3& operator*=(byte aRhs);
	byte3& operator/=(byte aRhs);


	// Dot Product
	byte operator*(const byte3& aRhs) const;
	// Cross Product (Only exists in 3D)
	byte3 operator^(const byte3& aRhs) const;

};

byte3 operator+(byte aLhs, const byte3& aRhs);
byte3 operator-(byte aLhs, const byte3& aRhs);
byte3 operator*(byte aLhs, const byte3& aRhs);

#endif // !GEODESUKA_CORE_MATH_UBYTE3_H
