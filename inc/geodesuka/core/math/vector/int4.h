#pragma once
#ifndef GEODESUKA_CORE_MATH_INT4_H
#define GEODESUKA_CORE_MATH_INT4_H

#include "../config.h"

#include "../number/type.h"

union int4 {
	struct {
		int x, y, z, t;
	};
	struct {
		int r, g, b, a;
	};
	int ptr[4];

	int4() : x(0u), y(0u), z(0u), t(0u) {}
	int4(int A) : x(A), y(A), z(A), t(A) {}
	int4(int X, int Y, int Z, int T) : x(X), y(Y), z(Z), t(T) {}
	
	// Vector Space Stuff.
	int4&	operator=(int aRhs);
	int4&	operator=(const int4& aRhs);
	int4&	operator=(int4&& aRhs) noexcept;

	// Access
	int	operator[](int aIndex) const;
	int&	operator[](int aIndex);

	// Vector addition and subtraction.
	int4	operator-() const;
	int4	operator+(int aRhs) const;
	int4	operator+(const int4& aRhs) const;
	int4	operator-(int aRhs) const;
	int4	operator-(const int4& aRhs) const;
	int4&	operator+=(int aRhs);
	int4&	operator+=(const int4& aRhs);
	int4&	operator-=(int aRhs);
	int4&	operator-=(const int4& aRhs);

	// Scalar multiplication & division.
	int4	operator*(int aRhs) const;
	int4	operator/(int aRhs) const;
	int4&	operator*=(int aRhs);
	int4&	operator/=(int aRhs);


	// Dot Product
	int	operator*(const int4& aRhs) const;
	// Cross Product (Only exists in 3D)
	//int4	operator^(const int4& aRhs) const;

};

int4 operator+(int aLhs, const int4& aRhs);
int4 operator-(int aLhs, const int4& aRhs);
int4 operator*(int aLhs, const int4& aRhs);

#endif // !GEODESUKA_CORE_MATH_INT4_H
