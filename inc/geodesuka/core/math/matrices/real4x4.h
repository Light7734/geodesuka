#pragma once
#ifndef REAL4X4_H
#define REAL4X4_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/integer.h"
#include "../vectors/integer2.h"

#include "../numbers/real.h"
#include "../vectors/real2.h"
#include "../vectors/real3.h"
#include "../vectors/real4.h"

#include "real2x2.h"
#include "real3x3.h"

namespace geodesuka {
	namespace core {
		namespace math {

			union real4x4 {
				static const real4x4 I;
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				struct {
					real xx, xy, xz, xt;
					real yx, yy, yz, yt;
					real zx, zy, zz, zt;
					real tx, ty, tz, tt;
				};
#else
				// Column Major Memory Layout
				struct {
					real xx, yx, zx, tx;
					real xy, yy, zy, ty;
					real xz, yz, zz, tz;
					real xt, yt, zt, tt;
				};
#endif // !COL_MAJOR_MEMORY_LAYOUT
				//struct {
				//	real4 x, y, z, t;
				//};
				//real4 vptr[4];
				real aptr[4][4];
				real ptr[4 * 4];

				real4x4() :
					xx(0.0), xy(0.0), xz(0.0), xt(0.0),
					yx(0.0), yy(0.0), yz(0.0), yt(0.0),
					zx(0.0), zy(0.0), zz(0.0), zt(0.0),
					tx(0.0), ty(0.0), tz(0.0), tt(0.0)
				{}
				real4x4(
					real XX, real XY, real XZ, real XT,
					real YX, real YY, real YZ, real YT,
					real ZX, real ZY, real ZZ, real ZT,
					real TX, real TY, real TZ, real TT
				) :
					xx(XX), xy(XY), xz(XZ), xt(XT),
					yx(YX), yy(YY), yz(YZ), yt(YT),
					zx(ZX), zy(ZY), zz(ZZ), zt(ZT),
					tx(TX), ty(TY), tz(TZ), tt(TT)
				{}
				real4x4(
					const real2x2& A, const real2x2& B,
					const real2x2& C, const real2x2& D
				) :
					xx(A.xx), xy(A.xy), xz(B.xx), xt(B.xy),
					yx(A.yx), yy(A.yy), yz(B.yx), yt(B.yy),
					zx(C.xx), zy(C.xy), zz(D.xx), zt(D.xy),
					tx(C.yx), ty(C.yy), tz(D.yx), tt(D.yy)
				{}
				real4x4(const real4& Col1, const real4& Col2, const real4& Col3, const real4& Col4) :
					xx(Col1.x), xy(Col2.x), xz(Col3.x), xt(Col4.x),
					yx(Col1.y), yy(Col2.y), yz(Col3.y), yt(Col4.y),
					zx(Col1.z), zy(Col2.z), zz(Col3.z), zt(Col4.z),
					tx(Col1.t), ty(Col2.t), tz(Col3.t), tt(Col4.t)
				{}
				~real4x4() {}

				// Access elements of matrix in standard notation.
				real operator()(integer RowElement, integer ColumnElement) const;
				real& operator()(integer RowElement, integer ColumnElement);

				real4x4 operator-() const;
				real4x4 operator+(const real4x4& Rhs) const;
				real4x4 operator-(const real4x4& Rhs) const;
				real4x4 operator*(const real4x4& Rhs) const;

				real4x4& operator+=(const real4x4& Rhs);
				real4x4& operator-=(const real4x4& Rhs);
				real4x4& operator*=(const real4x4& Rhs);

				// Multiply column vector
				real4 operator*(const real4& Rhs) const;
				// Scalar Multiplication
				real4x4 operator*(real Rhs) const;
				real4x4 operator/(real Rhs) const;

				real3x3 sub(integer RowElement, integer ColumnElement) const;
				void setr(const real4& Row1, const real4& Row2, const real4& Row3, const real4& Row4);
				void setc(const real4& Col1, const real4& Col2, const real4& Col3, const real4& Col4);

			};

			real4 operator*(const real4& Lhs, const real4x4& Rhs);
			real4x4 operator*(real Lhs, const real4x4& Rhs);

			real det(const real4x4& Arg);
			real tr(const real4x4& Arg);
			//real4x4 diag(const real4x4& Arg);
			real4x4 transpose(const real4x4& Arg);
			//real4x4 inverse(const real4x4& Arg);

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real4x4& Arg);
#endif // MATH_ENABLE_IO

		}
	}
}

#endif // !REAL4X4_H
