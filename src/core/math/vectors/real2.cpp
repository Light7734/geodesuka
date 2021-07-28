#include <geodesuka/core/math/vectors/real2.h>

//// Standard C Libraries
////#include <assert.h>
//#include <stdint.h>
//#include <float.h>
//#include <limits.h>
//#include <math.h>

#include <cmath>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/numbers/real.h>

namespace geodesuka {
	namespace core {
		namespace math {

			real2::real2() {
				this->x = 0.0; this->y = 0.0;
			}

			real2::~real2() {}
#ifdef CS_PLEB_NOTATION
			real2::real2(real Val) {
				this->x = Val; this->y = Val;
			}
#endif // CS_PLEB_NOTATION
			real2::real2(real ValX, real ValY) {
				this->x = ValX; this->y = ValY;
			}

			real2::real2(const real2& Val) {
				this->x = Val.x; this->y = Val.y;
			}
#ifdef CS_PLEB_NOTATION
			real2& real2::operator=(real Rhs) {
				this->x = Rhs; this->y = Rhs;
				return *this;
			}
#endif // CS_PLEB_NOTATION
			real2& real2::operator=(const real2& Rhs) {
				this->x = Rhs.x; this->y = Rhs.y;
				return *this;
			}

			real real2::operator[](integer Index) const {
				return this->ptr[Index];
			}

			real& real2::operator[](integer Index) {
				return this->ptr[Index];
			}

			real2 real2::operator-() const {
				return real2(-this->x, -this->y);
			}

			real2 real2::operator+(const real2& Rhs) const {
				return real2(this->x + Rhs.x, this->y + Rhs.y);
			}

			real2 real2::operator-(const real2& Rhs) const {
				return real2(this->x - Rhs.x, this->y - Rhs.y);
			}

			real real2::operator*(const real2& Rhs) const {
				return (this->x * Rhs.x + this->y * Rhs.y);
			}

			real real2::operator^(const real2& Rhs) const {
				return (this->x * Rhs.y - this->y * Rhs.x);
			}
			real2& real2::operator+=(const real2& Rhs) {
				*this = *this + Rhs;
				return *this;
			}
			real2& real2::operator-=(const real2& Rhs) {
				*this = *this - Rhs;
				return *this;
			}
#ifdef CS_PLEB_NOTATION
			real2 real2::operator+(real Rhs) const {
				return real2(this->x + Rhs, this->y + Rhs);
			}

			real2 real2::operator-(real Rhs) const {
				return real2(this->x - Rhs, this->y - Rhs);
			}
#endif // CS_PLEB_NOTATION
			real2 real2::operator*(real Rhs) const {
				return real2(this->x * Rhs, this->y * Rhs);
			}

			real2 real2::operator/(real Rhs) const {
				return real2(this->x / Rhs, this->y / Rhs);
			}
#ifdef CS_PLEB_NOTATION
			real2& real2::operator+=(real Rhs) {
				*this = *this + Rhs;
				return *this;
			}

			real2& real2::operator-=(real Rhs) {
				*this = *this - Rhs;
				return *this;
			}
#endif // CS_PLEB_NOTATION
			real2& real2::operator*=(real Rhs) {
				*this = *this * Rhs;
				return *this;
			}

			real2& real2::operator/=(real Rhs) {
				*this = *this / Rhs;
				return *this;
			}

#ifdef CS_PLEB_NOTATION
			real2 operator+(real Lhs, const real2& Rhs) {
				return real2(Lhs + Rhs.x, Lhs + Rhs.y);
			}

			real2 operator-(real Lhs, const real2& Rhs) {
				return real2(Lhs - Rhs.x, Lhs - Rhs.y);
			}
#endif // CS_PLEB_NOTATION
			real2 operator*(real Lhs, const real2& Rhs) {
				return real2(Lhs * Rhs.x, Lhs * Rhs.y);
			}
#ifdef CS_PLEB_NOTATION
			real2 operator/(real Lhs, const real2& Rhs) {
				return real2(Lhs / Rhs.x, Lhs / Rhs.y);
			}
#endif // CS_PLEB_NOTATION
			real length(const real2& Arg) {
				return sqrt(Arg * Arg);
			}

			real2 normalize(const real2& Arg) {
				return (real2(Arg) / length(Arg));
			}

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& os, const real2& v) {
				os << v.x << "ex + " << v.y << "ey";
				return os;
			}
#endif // MATH_ENABLE_IO

		}
	}
}