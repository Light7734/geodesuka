#pragma once
#ifndef GEODESUKA_CORE_MATH_BYTE2_H
#define GEODESUKA_CORE_MATH_BYTE2_H

#include "../config.h"

#include "../number/type.h"

union byte2 {
	struct {
		byte x, y;
	};
	struct {
		byte r, g;
	};
	byte ptr[2];

	byte2() : x(0u), y(0u) {}
	byte2(byte A) : x(A), y(A) {}
	byte2(byte X, byte Y) : x(X), y(Y) {}

	// Vector Space Stuff.
	byte2& operator=(byte aRhs);
	byte2& operator=(const byte2& aRhs);
	byte2& operator=(byte2&& aRhs) noexcept;

	// Access
	byte operator[](int aIndex) const;
	byte& operator[](int aIndex);

	// Vector addition and subtraction.
	byte2 operator-() const;
	byte2 operator+(byte aRhs) const;
	byte2 operator+(const byte2& aRhs) const;
	byte2 operator-(byte aRhs) const;
	byte2 operator-(const byte2& aRhs) const;
	byte2& operator+=(byte aRhs);
	byte2& operator+=(const byte2& aRhs);
	byte2& operator-=(byte aRhs);
	byte2& operator-=(const byte2& aRhs);

	// Scalar multiplication & division.
	byte2 operator*(byte aRhs) const;
	byte2 operator/(byte aRhs) const;
	byte2& operator*=(byte aRhs);
	byte2& operator/=(byte aRhs);


	// Dot Product
	byte operator*(const byte2& aRhs) const;
	// Cross Product (Only exists in 3D)
	byte2 operator^(const byte2& aRhs) const;

};

byte2 operator+(byte aLhs, const byte2& aRhs);
byte2 operator-(byte aLhs, const byte2& aRhs);
byte2 operator*(byte aLhs, const byte2& aRhs);

#endif // !GEODESUKA_CORE_MATH_BYTE2_H
