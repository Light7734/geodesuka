#pragma once
#ifndef GEODESUKA_CORE_MATH_BYTE4_H
#define GEODESUKA_CORE_MATH_BYTE4_H

#include "../config.h"

#include "../number/type.h"

union byte4 {
	struct {
		byte x, y, z, t;
	};
	struct {
		byte r, g, b, a;
	};
	byte ptr[4];

	byte4() : x(0u), y(0u), z(0u), t(0u) {}
	byte4(byte A) : x(A), y(A), z(A), t(A) {}
	byte4(byte X, byte Y, byte Z, byte T) : x(X), y(Y), z(Z), t(T) {}

	// Vector Space Stuff.
	byte4& operator=(byte aRhs);
	byte4& operator=(const byte4& aRhs);
	byte4& operator=(byte4&& aRhs) noexcept;

	// Access
	byte operator[](int aIndex) const;
	byte& operator[](int aIndex);

	// Vector addition and subtraction.
	byte4 operator-() const;
	byte4 operator+(byte aRhs) const;
	byte4 operator+(const byte4& aRhs) const;
	byte4 operator-(byte aRhs) const;
	byte4 operator-(const byte4& aRhs) const;
	byte4& operator+=(byte aRhs);
	byte4& operator+=(const byte4& aRhs);
	byte4& operator-=(byte aRhs);
	byte4& operator-=(const byte4& aRhs);

	// Scalar multiplication & division.
	byte4 operator*(byte aRhs) const;
	byte4 operator/(byte aRhs) const;
	byte4& operator*=(byte aRhs);
	byte4& operator/=(byte aRhs);


	// Dot Product
	byte	operator*(const byte4& aRhs) const;
	// Cross Product (Only exists in 3D)
	//byte4	operator^(const byte4& aRhs) const;

};

byte4 operator+(byte aLhs, const byte4& aRhs);
byte4 operator-(byte aLhs, const byte4& aRhs);
byte4 operator*(byte aLhs, const byte4& aRhs);

#endif // !GEODESUKA_CORE_MATH_UBYTE4_H
