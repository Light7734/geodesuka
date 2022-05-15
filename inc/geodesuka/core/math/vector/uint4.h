#pragma once
#ifndef GEODESUKA_CORE_MATH_UINT4_H
#define GEODESUKA_CORE_MATH_UINT4_H

#include "../config.h"

#include "../number/type.h"

union uint4 {
	struct {
		uint x, y, z, t;
	};
	struct {
		uint r, g, b, a;
	};
	uint ptr[4];

	uint4() : x(0u), y(0u), z(0u), t(0u) {}
	uint4(uint A) : x(A), y(A), z(A), t(A) {}
	uint4(uint X, uint Y, uint Z, uint T) : x(X), y(Y), z(Z), t(T) {}
	
	// Vector Space Stuff.
	uint4&	operator=(uint aRhs);
	//uint4&	operator=(const uint4& aRhs);
	//uint4&	operator=(uint4&& aRhs) noexcept;

	// Access
	uint	operator[](int aIndex) const;
	uint&	operator[](int aIndex);

	// Vector addition and subtraction.
	//uint4	operator-() const;
	uint4	operator+(uint aRhs) const;
	uint4	operator+(const uint4& aRhs) const;
	uint4	operator-(uint aRhs) const;
	uint4	operator-(const uint4& aRhs) const;
	uint4&	operator+=(uint aRhs);
	uint4&	operator+=(const uint4& aRhs);
	uint4&	operator-=(uint aRhs);
	uint4&	operator-=(const uint4& aRhs);

	// Scalar multiplication & division.
	uint4	operator*(uint aRhs) const;
	uint4	operator/(uint aRhs) const;
	uint4&	operator*=(uint aRhs);
	uint4&	operator/=(uint aRhs);


	// Dot Product
	uint	operator*(const uint4& aRhs) const;
	// Cross Product (Only exists in 3D)
	//uint4	operator^(const uint4& aRhs) const;

};

uint4 operator+(uint aLhs, const uint4& aRhs);
uint4 operator-(uint aLhs, const uint4& aRhs);
uint4 operator*(uint aLhs, const uint4& aRhs);

#endif // !GEODESUKA_CORE_MATH_UINT4_H
