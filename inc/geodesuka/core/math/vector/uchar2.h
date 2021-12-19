#pragma once
#ifndef GEODESUKA_CORE_MATH_UCHAR2_H
#define GEODESUKA_CORE_MATH_UCHAR2_H

#include "../config.h"

#include "../number/type.h"

union uchar2 {
	struct {
		uchar x, y;
	};
	struct {
		uchar r, g;
	};
	uchar ptr[2];

	uchar2() : x(0u), y(0u) {}
	uchar2(uchar A) : x(A), y(A) {}
	uchar2(uchar X, uchar Y) : x(X), y(Y) {}

	// Vector Space Stuff.
	uchar2& operator=(uchar aRhs);
	uchar2& operator=(const uchar2& aRhs);
	uchar2& operator=(uchar2&& aRhs) noexcept;

	// Access
	uchar	operator[](int aIndex) const;
	uchar& operator[](int aIndex);

	// Vector addition and subtraction.
	//uchar2	operator-() const;
	uchar2	operator+(uchar aRhs) const;
	uchar2	operator+(const uchar2& aRhs) const;
	uchar2	operator-(uchar aRhs) const;
	uchar2	operator-(const uchar2& aRhs) const;
	uchar2& operator+=(uchar aRhs);
	uchar2& operator+=(const uchar2& aRhs);
	uchar2& operator-=(uchar aRhs);
	uchar2& operator-=(const uchar2& aRhs);

	// Scalar multiplication & division.
	uchar2	operator*(uchar aRhs) const;
	uchar2	operator/(uchar aRhs) const;
	uchar2& operator*=(uchar aRhs);
	uchar2& operator/=(uchar aRhs);


	// Dot Product
	uchar operator*(const uchar2& aRhs) const;
	// Cross Product (Only exists in 3D)
	//uchar2	operator^(const uchar2& aRhs) const;

};

uchar2 operator+(uchar aLhs, const uchar2& aRhs);
uchar2 operator-(uchar aLhs, const uchar2& aRhs);
uchar2 operator*(uchar aLhs, const uchar2& aRhs);

#endif // !GEODESUKA_CORE_MATH_UCHAR2_H
