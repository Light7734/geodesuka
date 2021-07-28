#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H

#include "../config.h"

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include "../numbers/integer.h"
#include "../numbers/natural.h"
#include "../numbers/real.h"

namespace geodesuka {
	namespace core {
		namespace math {

			union complex {
				static const complex i;
				struct {
					real a, b;
				};
				struct {
					real x, y;
				};
				real ptr[2];

				complex();
				~complex();

				complex(real Val);
				complex(real VReal, real VImag);
				complex(const complex& Val);

				complex& operator=(real Rhs);
				complex& operator=(const complex& Rhs);

				real& operator[](integer Index);

				//complex operator+();
				complex operator-() const;
				complex operator~() const;
				complex operator+(const complex& Rhs) const;
				complex operator-(const complex& Rhs) const;
				complex operator*(const complex& Rhs) const;
				complex operator/(const complex& Rhs) const;

				complex& operator+=(const complex& Rhs);
				complex& operator-=(const complex& Rhs);
				complex& operator*=(const complex& Rhs);
				complex& operator/=(const complex& Rhs);

				complex operator+(real Rhs) const;
				complex operator-(real Rhs) const;
				complex operator*(real Rhs) const;
				complex operator/(real Rhs) const;

				complex& operator+=(real Rhs);
				complex& operator-=(real Rhs);
				complex& operator*=(real Rhs);
				complex& operator/=(real Rhs);

			};

			complex operator+(real Lhs, const complex& Rhs);
			complex operator-(real Lhs, const complex& Rhs);
			complex operator*(real Lhs, const complex& Rhs);
			complex operator/(real Lhs, const complex& Rhs);

			real re(const complex& Arg);
			real im(const complex& Arg);

			real abs2(const complex& Arg);
			real abs(const complex& Arg);
			real phase(const complex& Arg);

			complex conj(const complex& Arg);

			complex sqrt(const complex& Arg);

			complex exp(const complex& Arg);
			complex ln(const complex& Arg);

			complex pow(const complex& Base, const complex& Exponent);
			//complex log(const complex& Base, const complex& RetVal);

			complex sin(const complex& Arg);
			complex cos(const complex& Arg);
			complex tan(const complex& Arg);

			complex sinh(const complex& Arg);
			complex cosh(const complex& Arg);
			complex tanh(const complex& Arg);

			complex asin(const complex& Arg);
			complex acos(const complex& Arg);
			complex atan(const complex& Arg);

			complex asinh(const complex& Arg);
			complex acosh(const complex& Arg);
			complex atanh(const complex& Arg);

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const complex& Arg);
#endif // MATH_ENABLE_IO

		}
	}
}

#endif // !COMPLEX_H
