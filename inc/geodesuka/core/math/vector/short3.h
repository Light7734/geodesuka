#pragma once
#ifndef GEODESUKA_CORE_MATH_SHORT3_H
#define GEODESUKA_CORE_MATH_SHORT3_H

#include "../config.h"

#include "../number/type.h"

union short3 {
	struct {
		short x, y, z;
	};
	struct {
		short r, g, b;
	};
	short ptr[3];

	short3() : x(0u), y(0u), z(0u) {}
	short3(short A) : x(A), y(A), z(A) {}
	short3(short X, short Y, short Z) : x(X), y(Y), z(Z) {}

	// Vector Space Stuff.
	short3& operator=(short aRhs);
	//short3& operator=(const short3& aRhs);
	//short3& operator=(short3&& aRhs) noexcept;

	// Access
	short operator[](int aIndex) const;
	short& operator[](int aIndex);

	// Vector addition and subtraction.
	short3 operator-() const;
	short3 operator+(short aRhs) const;
	short3 operator+(const short3& aRhs) const;
	short3 operator-(short aRhs) const;
	short3 operator-(const short3& aRhs) const;
	short3& operator+=(short aRhs);
	short3& operator+=(const short3& aRhs);
	short3& operator-=(short aRhs);
	short3& operator-=(const short3& aRhs);

	// Scalar multiplication & division.
	short3 operator*(short aRhs) const;
	short3 operator/(short aRhs) const;
	short3& operator*=(short aRhs);
	short3& operator/=(short aRhs);


	// Dot Product
	short operator*(const short3& aRhs) const;
	// Cross Product (Only exists in 3D)
	short3 operator^(const short3& aRhs) const;

};

short3 operator+(short aLhs, const short3& aRhs);
short3 operator-(short aLhs, const short3& aRhs);
short3 operator*(short aLhs, const short3& aRhs);

#endif // !GEODESUKA_CORE_MATH_UBYTE3_H
