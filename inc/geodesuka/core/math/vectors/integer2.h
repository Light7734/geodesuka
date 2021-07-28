#pragma once
#ifndef INTEGER2_H
#define INTEGER2_H

#include "../config.h"

#include "../numbers/integer.h"

namespace geodesuka {
	namespace core {
		namespace math {

			union integer2 {
				struct {
					integer x, y;
				};
				struct {
					integer a, b;
				};
				integer ptr[2];

				integer2();
				~integer2();

#ifdef CS_PLEB_NOTATION
				integer2(integer Arg);
#endif // CS_PLEB_NOTATION
				integer2(integer ArgX, integer ArgY);
				integer2(const integer2& Arg);

#ifdef CS_PLEB_NOTATION
				integer2& operator=(integer Rhs);
#endif // CS_PLEB_NOTATION
				integer2& operator=(const integer2& Rhs);

				integer operator[](integer Index) const;
				integer& operator[](integer Index);

				integer2 operator-() const;
				integer2 operator+(const integer2& Rhs) const;
				integer2 operator-(const integer2& Rhs) const;
				integer operator*(const integer2& Rhs) const;
				integer operator^(const integer2& Rhs) const;

				integer2& operator+=(const integer2& Rhs);
				integer2& operator-=(const integer2& Rhs);

#ifdef CS_PLEB_NOTATION
				integer2 operator+(integer Rhs) const;
				integer2 operator-(integer Rhs) const;
#endif // CS_PLEB_NOTATION
				integer2 operator*(integer Rhs) const;
				integer2 operator/(integer Rhs) const;

#ifdef CS_PLEB_NOTATION
				integer2& operator+=(integer Rhs);
				integer2& operator-=(integer Rhs);
#endif // CS_PLEB_NOTATION
				integer2& operator*=(integer Rhs);
				integer2& operator/=(integer Rhs);

			};

#ifdef CS_PLEB_NOTATION
			integer2 operator+(integer Lhs, const integer2& Rhs);
			integer2 operator-(integer Lhs, const integer2& Rhs);
#endif // CS_PLEB_NOTATION
			integer2 operator*(integer Lhs, const integer2& Rhs);
#ifdef CS_PLEB_NOTATION
			integer2 operator/(integer Lhs, const integer2& Rhs);
#endif // CS_PLEB_NOTATION

		}
	}
}

#endif // !INTEGER2_H
