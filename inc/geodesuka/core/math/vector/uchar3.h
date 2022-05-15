#pragma once
#ifndef GEODESUKA_CORE_MATH_UCHAR3_H
#define GEODESUKA_CORE_MATH_UCHAR3_H

#include "../config.h"

#include "../number/type.h"

union uchar3 {
	struct {
		uchar x, y, z;
	};
	struct {
		uchar r, g, b;
	};
	uchar ptr[3];

	uchar3() : x(0u), y(0u), z(0u) {}
	uchar3(uchar A) : x(A), y(A), z(A) {}
	uchar3(uchar X, uchar Y, uchar Z) : x(X), y(Y), z(Z) {}

	// Vector Space Stuff.
	uchar3& operator=(uchar aRhs);
	//uchar3& operator=(const uchar3& aRhs);
	//uchar3& operator=(uchar3&& aRhs) noexcept;

	// Access
	uchar	operator[](int aIndex) const;
	uchar& operator[](int aIndex);

	// Vector addition and subtraction.
	//uchar3	operator-() const;
	uchar3	operator+(uchar aRhs) const;
	uchar3	operator+(const uchar3& aRhs) const;
	uchar3	operator-(uchar aRhs) const;
	uchar3	operator-(const uchar3& aRhs) const;
	uchar3& operator+=(uchar aRhs);
	uchar3& operator+=(const uchar3& aRhs);
	uchar3& operator-=(uchar aRhs);
	uchar3& operator-=(const uchar3& aRhs);

	// Scalar multiplication & division.
	uchar3	operator*(uchar aRhs) const;
	uchar3	operator/(uchar aRhs) const;
	uchar3& operator*=(uchar aRhs);
	uchar3& operator/=(uchar aRhs);


	// Dot Product
	uchar operator*(const uchar3& aRhs) const;
	// Cross Product (Only exists in 3D)
	//uchar3	operator^(const uchar3& aRhs) const;

};

uchar3 operator+(uchar aLhs, const uchar3& aRhs);
uchar3 operator-(uchar aLhs, const uchar3& aRhs);
uchar3 operator*(uchar aLhs, const uchar3& aRhs);

#endif // !GEODESUKA_CORE_MATH_UCHAR3_H
