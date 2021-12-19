#pragma once
#ifndef GEODESUKA_CORE_MATH_UBYTE3_H
#define GEODESUKA_CORE_MATH_UBYTE3_H

#include "../config.h"

#include "../number/type.h"

union ubyte3 {
	struct {
		ubyte x, y, z;
	};
	struct {
		ubyte r, g, b;
	};
	ubyte ptr[3];

	ubyte3() : x(0u), y(0u), z(0u) {}
	ubyte3(ubyte A) : x(A), y(A), z(A) {}
	ubyte3(ubyte X, ubyte Y, ubyte Z) : x(X), y(Y), z(Z) {}

	// Vector Space Stuff.
	ubyte3& operator=(ubyte aRhs);
	ubyte3& operator=(const ubyte3& aRhs);
	ubyte3& operator=(ubyte3&& aRhs) noexcept;

	// Access
	ubyte	operator[](int aIndex) const;
	ubyte& operator[](int aIndex);

	// Vector addition and subtraction.
	//ubyte3	operator-() const;
	ubyte3	operator+(ubyte aRhs) const;
	ubyte3	operator+(const ubyte3& aRhs) const;
	ubyte3	operator-(ubyte aRhs) const;
	ubyte3	operator-(const ubyte3& aRhs) const;
	ubyte3& operator+=(ubyte aRhs);
	ubyte3& operator+=(const ubyte3& aRhs);
	ubyte3& operator-=(ubyte aRhs);
	ubyte3& operator-=(const ubyte3& aRhs);

	// Scalar multiplication & division.
	ubyte3	operator*(ubyte aRhs) const;
	ubyte3	operator/(ubyte aRhs) const;
	ubyte3& operator*=(ubyte aRhs);
	ubyte3& operator/=(ubyte aRhs);


	// Dot Product
	ubyte operator*(const ubyte3& aRhs) const;
	// Cross Product (Only exists in 3D)
	//ubyte3	operator^(const ubyte3& aRhs) const;

};

ubyte3 operator+(ubyte aLhs, const ubyte3& aRhs);
ubyte3 operator-(ubyte aLhs, const ubyte3& aRhs);
ubyte3 operator*(ubyte aLhs, const ubyte3& aRhs);

#endif // !GEODESUKA_CORE_MATH_UBYTE3_H
