#pragma once
#ifndef GEODESUKA_CORE_MATH_SHORT4_H
#define GEODESUKA_CORE_MATH_SHORT4_H

#include "../config.h"

#include "../number/type.h"

union short4 {
	struct {
		short x, y, z, t;
	};
	struct {
		short r, g, b, a;
	};
	short ptr[4];

	short4() : x(0u), y(0u), z(0u), t(0u) {}
	short4(short A) : x(A), y(A), z(A), t(A) {}
	short4(short X, short Y, short Z, short T) : x(X), y(Y), z(Z), t(T) {}

	// Vector Space Stuff.
	short4& operator=(short aRhs);
	//short4& operator=(const short4& aRhs);
	//short4& operator=(short4&& aRhs) noexcept;

	// Access
	short	operator[](int aIndex) const;
	short& operator[](int aIndex);

	// Vector addition and subtraction.
	short4 operator-() const;
	short4 operator+(short aRhs) const;
	short4 operator+(const short4& aRhs) const;
	short4 operator-(short aRhs) const;
	short4 operator-(const short4& aRhs) const;
	short4& operator+=(short aRhs);
	short4& operator+=(const short4& aRhs);
	short4& operator-=(short aRhs);
	short4& operator-=(const short4& aRhs);

	// Scalar multiplication & division.
	short4 operator*(short aRhs) const;
	short4 operator/(short aRhs) const;
	short4& operator*=(short aRhs);
	short4& operator/=(short aRhs);


	// Dot Product
	short	operator*(const short4& aRhs) const;
	// Cross Product (Only exists in 3D)
	//short4	operator^(const short4& aRhs) const;

};

short4 operator+(short aLhs, const short4& aRhs);
short4 operator-(short aLhs, const short4& aRhs);
short4 operator*(short aLhs, const short4& aRhs);

#endif // !GEODESUKA_CORE_MATH_UBYTE4_H
