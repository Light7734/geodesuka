#pragma once
#ifndef GEODESUKA_CORE_MATH_UCHAR4_H
#define GEODESUKA_CORE_MATH_UCHAR4_H

#include "../config.h"

#include "../number/type.h"

union uchar4 {
	struct {
		uchar x, y, z, t;
	};
	struct {
		uchar r, g, b, a;
	};
	uchar ptr[4];

	uchar4() : x(0u), y(0u), z(0u), t(0u) {}
	uchar4(uchar A) : x(A), y(A), z(A), t(A) {}
	uchar4(uchar X, uchar Y, uchar Z, uchar T) : x(X), y(Y), z(Z), t(T) {}

	// Vector Space Stuff.
	uchar4& operator=(uchar aRhs);
	uchar4& operator=(const uchar4& aRhs);
	uchar4& operator=(uchar4&& aRhs) noexcept;

	// Access
	uchar	operator[](int aIndex) const;
	uchar&	operator[](int aIndex);

	// Vector addition and subtraction.
	//uchar4	operator-() const;
	uchar4	operator+(uchar aRhs) const;
	uchar4	operator+(const uchar4& aRhs) const;
	uchar4	operator-(uchar aRhs) const;
	uchar4	operator-(const uchar4& aRhs) const;
	uchar4&	operator+=(uchar aRhs);
	uchar4&	operator+=(const uchar4& aRhs);
	uchar4&	operator-=(uchar aRhs);
	uchar4&	operator-=(const uchar4& aRhs);

	// Scalar multiplication & division.
	uchar4	operator*(uchar aRhs) const;
	uchar4	operator/(uchar aRhs) const;
	uchar4&	operator*=(uchar aRhs);
	uchar4&	operator/=(uchar aRhs);


	// Dot Product
	uchar operator*(const uchar4& aRhs) const;
	// Cross Product (Only exists in 3D)
	//uchar4	operator^(const uchar4& aRhs) const;

};

uchar4 operator+(uchar aLhs, const uchar4& aRhs);
uchar4 operator-(uchar aLhs, const uchar4& aRhs);
uchar4 operator*(uchar aLhs, const uchar4& aRhs);

#endif // !GEODESUKA_CORE_MATH_UCHAR4_H
