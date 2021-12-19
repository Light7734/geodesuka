#pragma once
#ifndef GEODESUKA_CORE_MATH_UBYTE4_H
#define GEODESUKA_CORE_MATH_UBYTE4_H

#include "../config.h"

#include "../number/type.h"

union ubyte4 {
	struct {
		ubyte x, y, z, t;
	};
	struct {
		ubyte r, g, b, a;
	};
	ubyte ptr[4];

	ubyte4() : x(0u), y(0u), z(0u), t(0u) {}
	ubyte4(ubyte A) : x(A), y(A), z(A), t(A) {}
	ubyte4(ubyte X, ubyte Y, ubyte Z, ubyte T) : x(X), y(Y), z(Z), t(T) {}

	// Vector Space Stuff.
	ubyte4& operator=(ubyte aRhs);
	ubyte4& operator=(const ubyte4& aRhs);
	ubyte4& operator=(ubyte4&& aRhs) noexcept;

	// Access
	ubyte	operator[](int aIndex) const;
	ubyte&	operator[](int aIndex);

	// Vector addition and subtraction.
	//ubyte4	operator-() const;
	ubyte4	operator+(ubyte aRhs) const;
	ubyte4	operator+(const ubyte4& aRhs) const;
	ubyte4	operator-(ubyte aRhs) const;
	ubyte4	operator-(const ubyte4& aRhs) const;
	ubyte4&	operator+=(ubyte aRhs);
	ubyte4&	operator+=(const ubyte4& aRhs);
	ubyte4&	operator-=(ubyte aRhs);
	ubyte4&	operator-=(const ubyte4& aRhs);

	// Scalar multiplication & division.
	ubyte4	operator*(ubyte aRhs) const;
	ubyte4	operator/(ubyte aRhs) const;
	ubyte4&	operator*=(ubyte aRhs);
	ubyte4&	operator/=(ubyte aRhs);


	// Dot Product
	ubyte operator*(const ubyte4& aRhs) const;
	// Cross Product (Only exists in 3D)
	//ubyte4	operator^(const ubyte4& aRhs) const;

};

ubyte4 operator+(ubyte aLhs, const ubyte4& aRhs);
ubyte4 operator-(ubyte aLhs, const ubyte4& aRhs);
ubyte4 operator*(ubyte aLhs, const ubyte4& aRhs);

#endif // !GEODESUKA_CORE_MATH_UBYTE4_H
