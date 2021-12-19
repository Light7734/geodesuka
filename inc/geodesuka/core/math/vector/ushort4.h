#pragma once
#ifndef GEODESUKA_CORE_MATH_USHORT4_H
#define GEODESUKA_CORE_MATH_USHORT4_H

#include "../config.h"

#include "../number/type.h"

union ushort4 {
	struct {
		ushort x, y, z, t;
	};
	struct {
		ushort r, g, b, a;
	};
	ushort ptr[4];

	ushort4() : x(0u), y(0u), z(0u), t(0u) {}
	ushort4(ushort A) : x(A), y(A), z(A), t(A) {}
	ushort4(ushort X, ushort Y, ushort Z, ushort T) : x(X), y(Y), z(Z), t(T) {}
	
	// Vector Space Stuff.
	ushort4& operator=(ushort aRhs);
	ushort4& operator=(const ushort4& aRhs);
	ushort4& operator=(ushort4&& aRhs) noexcept;

	// Access
	ushort	operator[](int aIndex) const;
	ushort&	operator[](int aIndex);

	// Vector addition and subtraction.
	//ushort4	operator-() const;
	ushort4		operator+(ushort aRhs) const;
	ushort4		operator+(const ushort4& aRhs) const;
	ushort4		operator-(ushort aRhs) const;
	ushort4		operator-(const ushort4& aRhs) const;
	ushort4&	operator+=(ushort aRhs);
	ushort4&	operator+=(const ushort4& aRhs);
	ushort4&	operator-=(ushort aRhs);
	ushort4&	operator-=(const ushort4& aRhs);

	// Scalar multiplication & division.
	ushort4		operator*(ushort aRhs) const;
	ushort4		operator/(ushort aRhs) const;
	ushort4&	operator*=(ushort aRhs);
	ushort4&	operator/=(ushort aRhs);


	// Dot Product
	ushort operator*(const ushort4& aRhs) const;
	// Cross Product (Only exists in 3D)
	//ushort4	operator^(const ushort4& aRhs) const;

};

ushort4 operator+(ushort aLhs, const ushort4& aRhs);
ushort4 operator-(ushort aLhs, const ushort4& aRhs);
ushort4 operator*(ushort aLhs, const ushort4& aRhs);

#endif // !GEODESUKA_CORE_MATH_USHORT4_H
