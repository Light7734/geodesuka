#pragma once
#ifndef GEODESUKA_CORE_MATH_USHORT3_H
#define GEODESUKA_CORE_MATH_USHORT3_H

#include "../config.h"

#include "../number/type.h"

union ushort3 {
	struct {
		ushort x, y, z;
	};
	struct {
		ushort r, g, b;
	};
	ushort ptr[3];

	ushort3() : x(0u), y(0u), z(0u) {}
	ushort3(ushort A) : x(A), y(A), z(A) {}
	ushort3(ushort X, ushort Y, ushort Z) : x(X), y(Y), z(Z) {}
	
	// Vector Space Stuff.
	ushort3& operator=(ushort aRhs);
	ushort3& operator=(const ushort3& aRhs);
	ushort3& operator=(ushort3&& aRhs) noexcept;

	// Access
	ushort	operator[](int aIndex) const;
	ushort&	operator[](int aIndex);

	// Vector addition and subtraction.
	//ushort3	operator-() const;
	ushort3		operator+(ushort aRhs) const;
	ushort3		operator+(const ushort3& aRhs) const;
	ushort3		operator-(ushort aRhs) const;
	ushort3		operator-(const ushort3& aRhs) const;
	ushort3&	operator+=(ushort aRhs);
	ushort3&	operator+=(const ushort3& aRhs);
	ushort3&	operator-=(ushort aRhs);
	ushort3&	operator-=(const ushort3& aRhs);

	// Scalar multiplication & division.
	ushort3		operator*(ushort aRhs) const;
	ushort3		operator/(ushort aRhs) const;
	ushort3&	operator*=(ushort aRhs);
	ushort3&	operator/=(ushort aRhs);


	// Dot Product
	ushort operator*(const ushort3& aRhs) const;
	// Cross Product (Only exists in 3D)
	//ushort3	operator^(const ushort3& aRhs) const;

};

ushort3 operator+(ushort aLhs, const ushort3& aRhs);
ushort3 operator-(ushort aLhs, const ushort3& aRhs);
ushort3 operator*(ushort aLhs, const ushort3& aRhs);

#endif // !GEODESUKA_CORE_MATH_USHORT3_H
