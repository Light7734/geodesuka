#pragma once
#ifndef GEODESUKA_CORE_MATH_USHORT2_H
#define GEODESUKA_CORE_MATH_USHORT2_H

#include "../config.h"

#include "../number/type.h"

union ushort2 {
	struct {
		ushort x, y;
	};
	struct {
		ushort r, g;
	};
	ushort ptr[2];

	ushort2() : x(0u), y(0u) {}
	ushort2(ushort A) : x(A), y(A) {}
	ushort2(ushort X, ushort Y) : x(X), y(Y) {}
	
	// Vector Space Stuff.
	ushort2& operator=(ushort aRhs);
	ushort2& operator=(const ushort2& aRhs);
	ushort2& operator=(ushort2&& aRhs) noexcept;

	// Access
	ushort	operator[](int aIndex) const;
	ushort&	operator[](int aIndex);

	// Vector addition and subtraction.
	//ushort2	operator-() const;
	ushort2		operator+(ushort aRhs) const;
	ushort2		operator+(const ushort2& aRhs) const;
	ushort2		operator-(ushort aRhs) const;
	ushort2		operator-(const ushort2& aRhs) const;
	ushort2&	operator+=(ushort aRhs);
	ushort2&	operator+=(const ushort2& aRhs);
	ushort2&	operator-=(ushort aRhs);
	ushort2&	operator-=(const ushort2& aRhs);

	// Scalar multiplication & division.
	ushort2		operator*(ushort aRhs) const;
	ushort2		operator/(ushort aRhs) const;
	ushort2&	operator*=(ushort aRhs);
	ushort2&	operator/=(ushort aRhs);


	// Dot Product
	ushort operator*(const ushort2& aRhs) const;
	// Cross Product (Only exists in 3D)
	//ushort2	operator^(const ushort2& aRhs) const;

};

ushort2 operator+(ushort aLhs, const ushort2& aRhs);
ushort2 operator-(ushort aLhs, const ushort2& aRhs);
ushort2 operator*(ushort aLhs, const ushort2& aRhs);

#endif // !GEODESUKA_CORE_MATH_USHORT2_H
