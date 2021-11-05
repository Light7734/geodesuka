#include <geodesuka/core/math/numbers/complex.h>

#include <cmath>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/numbers/natural.h>
#include <geodesuka/core/math/numbers/integer.h>
#include <geodesuka/core/math/numbers/real.h>
#include <geodesuka/core/math/numbers/constants.h>

namespace geodesuka::core::math {

	const complex complex::i = complex(0, 1);

	complex::complex() {
		this->a = 0.0; this->b = 0.0;
	}

	complex::~complex() {}

	complex::complex(real Val) {
		this->a = Val; this->b = 0.0;
	}


	complex::complex(real VReal, real VImag) {
		this->a = VReal; this->b = VImag;
	}

	complex::complex(const complex& Arg) {
		this->a = Arg.a; this->b = Arg.b;
	}

	complex& complex::operator=(real Rhs) {
		this->a = Rhs; this->b = 0.0;
		return *this;
	}

	complex& complex::operator=(const complex& Rhs) {
		this->a = Rhs.a; this->b = Rhs.b;
		return *this;
	}

	real& complex::operator[](integer Index) {
		return ptr[Index];
	}

	complex complex::operator-() const {
		return complex(-this->a, -this->b);
	}

	complex complex::operator~() const {
		return complex(this->a, -this->b);
	}

	complex complex::operator+(const complex& Rhs) const {
		return complex(this->a + Rhs.a, this->b + Rhs.b);
	}

	complex complex::operator-(const complex& Rhs) const {
		return complex(this->a - Rhs.a, this->b - Rhs.b);
	}

	complex complex::operator*(const complex& Rhs) const {
		return complex(this->a * Rhs.a - this->b * Rhs.b, this->a * Rhs.b + this->b * Rhs.a);
	}

	complex complex::operator/(const complex& Rhs) const {
		real NewR = abs(*this) / abs(Rhs);
		real DeltaPhase = phase(*this) - phase(Rhs);
		return NewR * complex(std::cos(DeltaPhase), std::sin(DeltaPhase));
	}

	complex& complex::operator+=(const complex& Rhs) {
		*this = *this + Rhs;
		return *this;
	}

	complex& complex::operator-=(const complex& Rhs) {
		*this = *this - Rhs;
		return *this;
	}

	complex& complex::operator*=(const complex& Rhs) {
		*this = *this * Rhs;
		return *this;
	}

	complex& complex::operator/=(const complex& Rhs) {
		*this = *this / Rhs;
		return *this;
	}

	complex complex::operator+(real Rhs) const {
		return complex(this->a + Rhs, this->b);
	}

	complex complex::operator-(real Rhs) const {
		return complex(this->a - Rhs, this->b);
	}

	complex complex::operator*(real Rhs) const {
		return complex(this->a * Rhs, this->b * Rhs);
	}

	complex complex::operator/(real Rhs) const {
		return complex(this->a / Rhs, this->b / Rhs);
	}

	complex& complex::operator+=(real Rhs) {
		*this = *this + Rhs;
		return *this;
	}

	complex& complex::operator-=(real Rhs) {
		*this = *this - Rhs;
		return *this;
	}

	complex& complex::operator*=(real Rhs) {
		*this = *this * Rhs;
		return *this;
	}

	complex& complex::operator/=(real Rhs) {
		*this = *this / Rhs;
		return *this;
	}

	complex operator+(real Lhs, const complex& Rhs) {
		return complex(Lhs + Rhs.a, Rhs.b);
	}

	complex operator-(real Lhs, const complex& Rhs) {
		return complex(Lhs - Rhs.a, -Rhs.b);
	}

	complex operator*(real Lhs, const complex& Rhs) {
		return complex(Lhs * Rhs.a, Lhs * Rhs.b);
	}

	complex operator/(real Lhs, const complex& Rhs) {
		return (Lhs / abs2(Rhs)) * conj(Rhs);
	}

	real re(const complex& Arg) {
		return Arg.a;
	}

	real im(const complex& Arg) {
		return Arg.b;
	}

	real abs2(const complex& Arg) {
		return Arg.a * Arg.a + Arg.b * Arg.b;
	}

	real abs(const complex& Arg) {
		return std::sqrt(abs2(Arg));
	}

	real phase(const complex& Arg) {
		return std::atan2(Arg.b, Arg.a);
	}

	complex conj(const complex& Arg) {
		return complex(Arg.a, -Arg.b);
	}

	complex sqrt(const complex& Arg) {
		real Mag = std::sqrt(abs(Arg));
		real Angle = 0.5 * phase(Arg);
		return Mag * complex(std::cos(Angle), std::sin(Angle));
	}

	complex exp(const complex& Arg) {
		return std::exp(Arg.a) * complex(std::cos(Arg.b), std::sin(Arg.b));
	}

	complex ln(const complex& Arg) {
		return complex(ln(abs(Arg)), phase(Arg));
	}

	complex pow(const complex& Base, const complex& Exponent) {
		return exp(Exponent * (ln(abs(Base)) + complex::i * phase(Base)));
	}

	complex sin(const complex& Arg) {
		return complex(std::sin(Arg.a) * std::cosh(Arg.b), std::cos(Arg.a) * std::sinh(Arg.b));
	}

	complex cos(const complex& Arg) {
		return complex(std::cos(Arg.a) * std::cosh(Arg.b), -std::sin(Arg.a) * std::sinh(Arg.b));
	}

	complex tan(const complex& Arg) {
		return sin(Arg) / cos(Arg);
	}

	complex sinh(const complex& Arg) {
		return complex(std::sinh(Arg.a) * std::cos(Arg.b), std::cosh(Arg.a) * std::sin(Arg.b));
	}

	complex cosh(const complex& Arg) {
		return complex(std::cosh(Arg.a) * std::cos(Arg.b), std::sinh(Arg.a) * std::sin(Arg.b));
	}

	complex tanh(const complex& Arg) {
		return (sinh(Arg) / cosh(Arg));
	}

	complex asin(const complex& Arg) {
		return (-complex::i * ln(complex::i * Arg + sqrt(1.0 - pow(Arg, 2.0))));
	}

	complex acos(const complex& Arg) {
		return (0.5 * constant::pi + complex::i * ln(complex::i * Arg + sqrt(1.0 - pow(Arg, 2.0))));
	}

	complex atan(const complex& Arg) {
		return (0.5 * complex::i * (ln(1.0 - complex::i * Arg) - ln(1.0 + complex::i * Arg)));
	}

	complex asinh(const complex& Arg) {
		return ln(Arg + sqrt(pow(Arg, 2.0) + 1.0));
	}

	complex acosh(const complex& Arg) {
		return ln(Arg + sqrt(Arg - 1.0) * sqrt(Arg + 1.0));
	}

	complex atanh(const complex& Arg) {
		return (0.5 * (ln(1.0 + Arg) - ln(1.0 - Arg)));
	}

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& Out, const complex& Arg) {

		if (Arg.a != 0.0) {
			Out << Arg.a;
		}

		if (Arg.b != 0.0) {
			if (Arg.b > 0.0) {
				if (Arg.a != 0.0) {
					Out << " + ";
				}
				Out << abs(Arg.b) << "i";
			}
			else {
				if (Arg.a != 0.0) {
					Out << " - ";
				}
				else {
					Out << "-";
				}
				Out << abs(Arg.b) << "i";
			}
		}

		return Out;
	}
#endif // MATH_ENABLE_IO

}