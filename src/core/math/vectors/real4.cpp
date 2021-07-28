#include <geodesuka/core/math/vectors/real4.h>

//// Standard C Libraries
////#include <assert.h>
//#include <stdint.h>
//#include <float.h>
//#include <limits.h>
//#include <math.h>

#include <string.h>

#include <cmath>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/numbers/integer.h>
#include <geodesuka/core/math/numbers/real.h>

namespace geodesuka {
	namespace core {
		namespace math {

			real4::real4() {
				this->x = 0.0; this->y = 0.0; this->z = 0.0; this->t = 0.0;
			}

			real4::~real4() {}
#ifdef CS_PLEB_NOTATION
			real4::real4(real Val) {
				this->x = Val; this->y = Val; this->z = Val; this->t = Val;
			}
#endif // CS_PLEB_NOTATION
			real4::real4(real ValX, real ValY, real ValZ, real ValT) {
				this->x = ValX; this->y = ValY; this->z = ValZ; this->t = ValT;
			}

			real4::real4(const real4& Val) {
				this->x = Val.x; this->y = Val.y; this->z = Val.z; this->t = Val.t;
			}
#ifdef CS_PLEB_NOTATION
			real4& real4::operator=(real Rhs) {
				this->x = Rhs; this->y = Rhs; this->z = Rhs; this->t = Rhs;
				return *this;
			}
#endif // CS_PLEB_NOTATION
			real4& real4::operator=(const real4& Rhs) {
				this->x = Rhs.x; this->y = Rhs.y; this->z = Rhs.z; this->t = Rhs.t;
				return *this;
			}

			real real4::operator[](integer Index) const {
				return this->ptr[Index];
			}

			real& real4::operator[](integer Index) {
				return this->ptr[Index];
			}

			real4 real4::operator-() const {
				return real4(-this->x, -this->y, -this->z, -this->t);
			}

			real4 real4::operator+(const real4& Rhs) const {
				return real4(this->x + Rhs.x, this->y + Rhs.y, this->z + Rhs.z, this->t + Rhs.t);
			}

			real4 real4::operator-(const real4& Rhs) const {
				return real4(this->x - Rhs.x, this->y - Rhs.y, this->z - Rhs.z, this->t - Rhs.t);
			}

			real real4::operator*(const real4& Rhs) const {
				return (this->x * Rhs.x + this->y * Rhs.y + this->z * Rhs.z + this->t * Rhs.t);
			}

			real4& real4::operator+=(const real4& Rhs) {
				*this = *this + Rhs;
				return *this;
			}

			real4& real4::operator-=(const real4& Rhs) {
				*this = *this - Rhs;
				return *this;
			}
#ifdef CS_PLEB_NOTATION
			real4 real4::operator+(real Rhs) const {
				return real4(this->x + Rhs, this->y + Rhs, this->z + Rhs, this->t + Rhs);
			}

			real4 real4::operator-(real Rhs) const {
				return real4(this->x - Rhs, this->y - Rhs, this->z - Rhs, this->t - Rhs);
			}
#endif // CS_PLEB_NOTATION
			real4 real4::operator*(real Rhs) const {
				return real4(this->x * Rhs, this->y * Rhs, this->z * Rhs, this->t * Rhs);
			}

			real4 real4::operator/(real Rhs) const {
				return real4(this->x / Rhs, this->y / Rhs, this->z / Rhs, this->t / Rhs);
			}
#ifdef CS_PLEB_NOTATION
			real4& real4::operator+=(real Rhs) {
				*this = *this + Rhs;
				return *this;
			}

			real4& real4::operator-=(real Rhs) {
				*this = *this - Rhs;
				return *this;
			}
#endif // CS_PLEB_NOTATION
			real4& real4::operator*=(real Rhs) {
				*this = *this * Rhs;
				return *this;
			}

			real4& real4::operator/=(real Rhs) {
				*this = *this / Rhs;
				return *this;
			}
#ifdef CS_PLEB_NOTATION
			real4 operator+(real Lhs, const real4& Rhs) {
				return real4(Lhs + Rhs.x, Lhs + Rhs.y, Lhs + Rhs.z, Lhs + Rhs.t);
			}

			real4 operator-(real Lhs, const real4& Rhs) {
				return real4(Lhs - Rhs.x, Lhs - Rhs.y, Lhs - Rhs.z, Lhs - Rhs.t);
			}
#endif // CS_PLEB_NOTATION
			real4 operator*(real Lhs, const real4& Rhs) {
				return real4(Lhs * Rhs.x, Lhs * Rhs.y, Lhs * Rhs.z, Lhs * Rhs.t);
			}
#ifdef CS_PLEB_NOTATION
			real4 operator/(real Lhs, const real4& Rhs) {
				return real4(Lhs / Rhs.x, Lhs / Rhs.y, Lhs / Rhs.z, Lhs / Rhs.t);
			}
#endif // CS_PLEB_NOTATION
			real length(const real4& Arg) {
				return sqrt(Arg * Arg);
			}

			real4 normalize(const real4& Arg) {
				return (Arg / length(Arg));
			}

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& os, const real4& v) {
				os << v.x << "ex + " << v.y << "ey + " << v.z << "ez + " << v.t << "et";
				return os;
			}
#endif // MATH_ENABLE_IO

		}
	}
}
