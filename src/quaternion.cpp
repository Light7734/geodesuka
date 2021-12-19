#include <geodesuka/core/math/number/quaternion.h>

#include <cmath>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/number/type.h>
#include <geodesuka/core/math/number/complex.h>

//tex:
// A quaternion can be writtin in the mathematical form.
// $$ q = a + b\hat{i} + c \hat{j} + d \hat{k} = a + \vec{v} $$
// A quaternion exponential can be written as
// $$ e^{q} = e^{a} ( \cos{v} + \hat{v} \cos{v} )$$
// A unit quaternion in the service of rotating a vector $\vec{r}$
// only needs to be defined in terms of another vector which it rotates
// around, and a quantity of of how much it rotates around.

//tex:
// The magnitude of the quaternion specifies the amount of rotation,
// while the unit vector specifies which vector is it to be rotated around.
// $$ \vec{r}^{'} = e^{\frac{\theta}{2} \hat{v}} \; \vec{r} \; e^{-\frac{\theta}{2}\hat{v}}$$

namespace geodesuka::core::math {

	const quaternion quaternion::i = quaternion(0, 1, 0, 0);
	const quaternion quaternion::j = quaternion(0, 0, 1, 0);
	const quaternion quaternion::k = quaternion(0, 0, 0, 1);

	quaternion::quaternion() {
		this->a = 0.0; this->b = 0.0; this->c = 0.0; this->d = 0.0;
	}

	quaternion::~quaternion() {
		this->a = 0.0; this->b = 0.0; this->c = 0.0; this->d = 0.0;
	}

	quaternion::quaternion(real Val) {
		this->a = Val; this->b = 0.0; this->c = 0.0; this->d = 0.0;
	}

	quaternion::quaternion(real VReal, real VImag) {
		this->a = VReal; this->b = VImag; this->c = 0.0; this->d = 0.0;
	}

	quaternion::quaternion(const complex& Val) {
		this->a = Val.a; this->b = Val.b; this->c = 0.0; this->d = 0.0;
	}

	quaternion::quaternion(real ValA, real ValB, real ValC, real ValD) {
		this->a = ValA; this->b = ValB; this->c = ValC; this->d = ValD;
	}

	quaternion::quaternion(const quaternion& Val) {
		this->a = Val.a; this->b = Val.b; this->c = Val.c; this->d = Val.d;
	}

	quaternion& quaternion::operator=(real Rhs) {
		this->a = Rhs; this->b = 0.0; this->c = 0.0; this->d = 0.0;
		return *this;
	}

	quaternion& quaternion::operator=(const complex& Rhs) {
		this->a = Rhs.a; this->b = Rhs.b; this->c = 0.0; this->d = 0.0;
		return *this;
	}

	quaternion& quaternion::operator=(const quaternion& Rhs) {
		this->a = Rhs.a; this->b = Rhs.b; this->c = Rhs.c; this->d = Rhs.d;
		return *this;
	}

	real& quaternion::operator[](integer Index) {
		return this->ptr[Index];
	}

	quaternion quaternion::operator-() const {
		return quaternion(-this->a, -this->b, -this->c, -this->d);
	}

	quaternion quaternion::operator~() const {
		return quaternion(this->a, -this->b, -this->c, -this->d);
	}

	quaternion quaternion::operator+(const quaternion& Rhs) const {
		return quaternion(this->a + Rhs.a, this->b + Rhs.b, this->c + Rhs.c, this->d + Rhs.d);
	}

	quaternion quaternion::operator-(const quaternion& Rhs) const {
		return quaternion(this->a - Rhs.a, this->b - Rhs.b, this->c - Rhs.c, this->d - Rhs.d);
	}

	quaternion quaternion::operator*(const quaternion& Rhs) const {
		return quaternion(
			this->a * Rhs.a - this->b * Rhs.b - this->c * Rhs.c - this->d * Rhs.d,
			this->a * Rhs.b + this->b * Rhs.a + this->c * Rhs.d - this->d * Rhs.c,
			this->a * Rhs.c - this->b * Rhs.d + this->c * Rhs.a + this->d * Rhs.b,
			this->a * Rhs.d + this->b * Rhs.c - this->c * Rhs.b + this->d * Rhs.a
		);
	}

	quaternion quaternion::operator/(const quaternion& Rhs) const {
		return ((*this) * (~Rhs)) / abs2(Rhs);
	}

	quaternion& quaternion::operator+=(const quaternion& Rhs) {
		*this = *this + Rhs;
		return *this;
	}

	quaternion& quaternion::operator-=(const quaternion& Rhs) {
		*this = *this - Rhs;
		return *this;
	}

	quaternion& quaternion::operator*=(const quaternion& Rhs) {
		*this = *this * Rhs;
		return *this;
	}

	quaternion& quaternion::operator/=(const quaternion& Rhs) {
		*this = *this / Rhs;
		return *this;
	}

	quaternion quaternion::operator+(const complex& Rhs) const {
		return (*this + quaternion(Rhs));
	}

	quaternion quaternion::operator-(const complex& Rhs) const {
		return (*this - quaternion(Rhs));
	}

	quaternion quaternion::operator*(const complex& Rhs) const {
		return (*this * quaternion(Rhs));
	}

	quaternion quaternion::operator/(const complex& Rhs) const {
		return (*this / quaternion(Rhs));
	}

	quaternion& quaternion::operator+=(const complex& Rhs) {
		*this += quaternion(Rhs);
		return *this;
	}

	quaternion& quaternion::operator-=(const complex& Rhs) {
		*this -= quaternion(Rhs);
		return *this;
	}

	quaternion& quaternion::operator*=(const complex& Rhs) {
		*this *= quaternion(Rhs);
		return *this;
	}

	quaternion& quaternion::operator/=(const complex& Rhs) {
		*this /= quaternion(Rhs);
		return *this;
	}

	quaternion quaternion::operator+(real Rhs) const {
		return quaternion(this->a + Rhs, this->b, this->c, this->d);
	}

	quaternion quaternion::operator-(real Rhs) const {
		return quaternion(this->a - Rhs, this->b, this->c, this->d);
	}

	quaternion quaternion::operator*(real Rhs) const {
		return quaternion(this->a * Rhs, this->b * Rhs, this->c * Rhs, this->d * Rhs);
	}

	quaternion quaternion::operator/(real Rhs) const {
		return quaternion(this->a / Rhs, this->b / Rhs, this->c / Rhs, this->d / Rhs);
	}

	quaternion& quaternion::operator+=(real Rhs) {
		*this = *this + Rhs;
		return *this;
	}

	quaternion& quaternion::operator-=(real Rhs) {
		*this = *this - Rhs;
		return *this;
	}

	quaternion& quaternion::operator*=(real Rhs) {
		*this = *this * Rhs;
		return *this;
	}

	quaternion& quaternion::operator/=(real Rhs) {
		*this = *this / Rhs;
		return *this;
	}

	quaternion operator+(const complex& Lhs, const quaternion& Rhs) {
		return quaternion(Lhs.a + Rhs.a, Lhs.b + Rhs.b, Rhs.c, Rhs.d);
	}

	quaternion operator-(const complex& Lhs, const quaternion& Rhs) {
		return quaternion(Lhs.a - Rhs.a, Lhs.b - Rhs.b, -Rhs.c, -Rhs.d);
	}

	quaternion operator*(const complex& Lhs, const quaternion& Rhs) {
		return quaternion(Lhs) * Rhs;
	}

	quaternion operator/(const complex& Lhs, const quaternion& Rhs) {
		return quaternion(Lhs) / Rhs;
	}

	quaternion operator+(real Lhs, const quaternion& Rhs) {
		return quaternion(Lhs + Rhs.a, Rhs.b, Rhs.c, Rhs.d);
	}

	quaternion operator-(real Lhs, const quaternion& Rhs) {
		return quaternion(Lhs - Rhs.a, -Rhs.b, -Rhs.c, -Rhs.d);
	}

	quaternion operator*(real Lhs, const quaternion& Rhs) {
		return quaternion(Lhs * Rhs.a, Lhs * Rhs.b, Lhs * Rhs.c, Lhs * Rhs.d);
	}

	quaternion operator/(real Lhs, const quaternion& Rhs) {
		return (Lhs / abs2(Rhs)) * (~Rhs);
	}

	real abs2(const quaternion& Arg) {
		return (Arg.a * Arg.a + Arg.b * Arg.b + Arg.c * Arg.c + Arg.d * Arg.d);
	}

	real abs(const quaternion& Arg) {
		return std::sqrt(abs2(Arg));
	}

	quaternion exp(const quaternion& Arg) {
		quaternion u = quaternion(0.0, Arg.b, Arg.c, Arg.d);
		real uMag = abs(u);
		return (std::exp(Arg.a) * (std::cos(uMag) + u * (std::sin(uMag) / uMag)));
	}

	quaternion ln(const quaternion& Arg) {
		quaternion u = quaternion(0.0, Arg.b, Arg.c, Arg.d);
		real Q = abs(Arg);
		real U = abs(u);
		return (ln(Q) + u * (std::acos(Arg.a / Q) / U));
	}

	quaternion pow(const quaternion& Base, const quaternion& Exponent) {
		return exp(ln(Base) * Exponent);
	}

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& os, const quaternion& q) {
		os << q.a << " + " << q.b << "i + " << q.c << "j + " << q.d << "k";
		return os;
	}
#endif // MATH_ENABLE_IO

}
