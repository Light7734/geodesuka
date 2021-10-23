#include <geodesuka/core/math/vectors/integer4.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/numbers/integer.h>

namespace geodesuka {
	namespace core {
		namespace math {

			integer4::integer4() {
				this->x = 0; this->y = 0; this->z = 0; this->t = 0;
			}

			integer4::~integer4() {}

#ifdef CS_PLEB_NOTATION
			integer4::integer4(integer Arg) {
				this->x = Arg; this->y = Arg; this->z = Arg; this->t = Arg;
			}
#endif // CS_PLEB_NOTATION
			integer4::integer4(integer ArgX, integer ArgY, integer ArgZ, integer ArgT) {
				this->x = ArgX; this->y = ArgY; this->z = ArgZ; this->t = ArgT;
			}

			integer4::integer4(const integer4& Arg) {
				this->x = Arg.x; this->y = Arg.y; this->z = Arg.z; this->t = Arg.t;
			}
#ifdef CS_PLEB_NOTATION
			integer4& integer4::operator=(integer Rhs) {
				this->x = Rhs; this->y = Rhs; this->z = Rhs; this->t = Rhs;
				return *this;
			}
#endif // CS_PLEB_NOTATION
			integer4& integer4::operator=(const integer4& Rhs) {
				this->x = Rhs.x; this->y = Rhs.y; this->z = Rhs.z; this->t = Rhs.t;
				return *this;
			}

			integer integer4::operator[](integer Index) const {
				return this->ptr[Index];
			}

			integer& integer4::operator[](integer Index) {
				return this->ptr[Index];
			}

			integer4 integer4::operator-() const {
				return integer4(-this->x, -this->y, -this->z, -this->t);
			}

			integer4 integer4::operator+(const integer4& Rhs) const {
				return integer4(this->x + Rhs.x, this->y + Rhs.y, this->z + Rhs.z, this->t + Rhs.t);
			}

			integer4 integer4::operator-(const integer4& Rhs) const {
				return integer4(this->x - Rhs.x, this->y - Rhs.y, this->z - Rhs.z, this->t - Rhs.t);
			}

			integer integer4::operator*(const integer4& Rhs) const {
				return (this->x * Rhs.x + this->y * Rhs.y + this->z * Rhs.z + this->t * Rhs.t);
			}

			integer4& integer4::operator+=(const integer4& Rhs) {
				*this = *this + Rhs;
				return *this;
			}

			integer4& integer4::operator-=(const integer4& Rhs) {
				*this = *this - Rhs;
				return *this;
			}

#ifdef CS_PLEB_NOTATION
			integer4 integer4::operator+(integer Rhs) const {
				return integer4(this->x + Rhs, this->y + Rhs, this->z + Rhs, this->t + Rhs);
			}

			integer4 integer4::operator-(integer Rhs) const {
				return integer4(this->x - Rhs, this->y - Rhs, this->z - Rhs, this->t - Rhs);
			}
#endif // CS_PLEB_NOTATION

			integer4 integer4::operator*(integer Rhs) const {
				return integer4(this->x * Rhs, this->y * Rhs, this->z * Rhs, this->t * Rhs);
			}

			integer4 integer4::operator/(integer Rhs) const {
				return integer4(this->x / Rhs, this->y / Rhs, this->z / Rhs, this->t / Rhs);
			}

#ifdef CS_PLEB_NOTATION
			integer4& integer4::operator+=(integer Rhs) {
				*this = *this + Rhs;
				return *this;
			}

			integer4& integer4::operator-=(integer Rhs) {
				*this = *this - Rhs;
				return *this;
			}
#endif // CS_PLEB_NOTATION

			integer4& integer4::operator*=(integer Rhs) {
				*this = *this * Rhs;
				return *this;
			}

			integer4& integer4::operator/=(integer Rhs) {
				*this = *this / Rhs;
				return *this;
			}
#ifdef CS_PLEB_NOTATION
			integer4 operator+(integer Lhs, const integer4& Rhs) {
				return integer4(Lhs + Rhs.x, Lhs + Rhs.y, Lhs + Rhs.z, Lhs + Rhs.t);
			}

			integer4 operator-(integer Lhs, const integer4& Rhs) {
				return integer4(Lhs - Rhs.x, Lhs - Rhs.y, Lhs - Rhs.z, Lhs - Rhs.t);
			}
#endif // CS_PLEB_NOTATION
			integer4 operator*(integer Lhs, const integer4& Rhs) {
				return integer4(Lhs * Rhs.x, Lhs * Rhs.y, Lhs * Rhs.z, Lhs * Rhs.t);
			}
#ifdef CS_PLEB_NOTATION
			integer4 operator/(integer Lhs, const integer4& Rhs) {
				return integer4(Lhs / Rhs.x, Lhs / Rhs.y, Lhs / Rhs.z, Lhs / Rhs.t);
			}
#endif // CS_PLEB_NOTATION

		}
	}
}
