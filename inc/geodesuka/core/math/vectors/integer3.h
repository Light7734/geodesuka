#pragma once
#ifndef INTEGER3_H
#define INTEGER3_H

#include "../config.h"

#include "../numbers/integer.h"

//struct integer3 {
//	integer x, y, z;
//};

namespace geodesuka {
	namespace core {
		namespace math {

			union integer3 {
				struct {
					integer x, y, z;
				};
				struct {
					integer r, g, b;
				};
				integer ptr[3];

				integer3();
				~integer3();

#ifdef CS_PLEB_NOTATION
				integer3(integer Arg);
#endif // CS_PLEB_NOTATION
				integer3(integer ArgX, integer ArgY, integer ArgZ);
				integer3(const integer3& Arg);

#ifdef CS_PLEB_NOTATION
				integer3& operator=(integer Rhs);
#endif // CS_PLEB_NOTATION
				integer3& operator=(const integer3& Rhs);

				integer operator[](integer Index) const;
				integer& operator[](integer Index);

				integer3 operator-() const;
				integer3 operator+(const integer3& Rhs) const;
				integer3 operator-(const integer3& Rhs) const;
				integer operator*(const integer3& Rhs) const;
				integer3 operator^(const integer3& Rhs) const;

				integer3& operator+=(const integer3& Rhs);
				integer3& operator-=(const integer3& Rhs);
				integer3& operator^=(const integer3& Rhs);

#ifdef CS_PLEB_NOTATION
				integer3 operator+(integer Rhs) const;
				integer3 operator-(integer Rhs) const;
#endif // CS_PLEB_NOTATION
				integer3 operator*(integer Rhs) const;
				integer3 operator/(integer Rhs) const;

#ifdef CS_PLEB_NOTATION
				integer3& operator+=(integer Rhs);
				integer3& operator-=(integer Rhs);
#endif // CS_PLEB_NOTATION
				integer3& operator*=(integer Rhs);
				integer3& operator/=(integer Rhs);

			};

#ifdef CS_PLEB_NOTATION
			integer3 operator+(integer Lhs, const integer3& Rhs);
			integer3 operator-(integer Lhs, const integer3& Rhs);
#endif // CS_PLEB_NOTATION
			integer3 operator*(integer Lhs, const integer3& Rhs);
#ifdef CS_PLEB_NOTATION
			integer3 operator/(integer Lhs, const integer3& Rhs);
#endif // CS_PLEB_NOTATION

		}
	}
}

#endif // !INTEGER3_H