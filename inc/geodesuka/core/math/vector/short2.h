#pragma once
#ifndef GEODESUKA_CORE_MATH_SHORT2_H
#define GEODESUKA_CORE_MATH_SHORT2_H

#include "../config.h"

#include "../number/type.h"

union short2 {
	struct {
		short x, y;
	};
	struct {
		short r, g;
	};
	short ptr[2];

	short2() : x(0u), y(0u) {}
	short2(short A) : x(A), y(A) {}
	short2(short X, short Y) : x(X), y(Y) {}

	// Vector Space Stuff.
	short2& operator=(short aRhs);
	short2& operator=(const short2& aRhs);
	short2& operator=(short2&& aRhs) noexcept;

	// Access
	short operator[](int aIndex) const;
	short& operator[](int aIndex);

	// Vector addition and subtraction.
	short2 operator-() const;
	short2 operator+(short aRhs) const;
	short2 operator+(const short2& aRhs) const;
	short2 operator-(short aRhs) const;
	short2 operator-(const short2& aRhs) const;
	short2& operator+=(short aRhs);
	short2& operator+=(const short2& aRhs);
	short2& operator-=(short aRhs);
	short2& operator-=(const short2& aRhs);

	// Scalar multiplication & division.
	short2 operator*(short aRhs) const;
	short2 operator/(short aRhs) const;
	short2& operator*=(short aRhs);
	short2& operator/=(short aRhs);


	// Dot Product
	short operator*(const short2& aRhs) const;
	// Cross Product (Only exists in 3D)
	short operator^(const short2& aRhs) const;

};

short2 operator+(short aLhs, const short2& aRhs);
short2 operator-(short aLhs, const short2& aRhs);
short2 operator*(short aLhs, const short2& aRhs);

#endif // !GEODESUKA_CORE_MATH_UBYTE2_H
