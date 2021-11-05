#include <geodesuka/core/math/matrices/real3x3.h>

#include <string.h>

#include <cmath>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/util/isupport.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/numbers/integer.h>
#include <geodesuka/core/math/vectors/integer2.h>
#include <geodesuka/core/math/vectors/integer3.h>

#include <geodesuka/core/math/numbers/real.h>
#include <geodesuka/core/math/vectors/real2.h>
#include <geodesuka/core/math/vectors/real3.h>
#include <geodesuka/core/math/vectors/real4.h>

namespace geodesuka::core::math {

	const real3x3 real3x3::I = real3x3(
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	);

	real3x3::real3x3(const real3& Col1, const real3& Col2, const real3& Col3) {
		//#ifdef ROW_MAJOR_MEMORY_LAYOUT
		//		// Row Major Memory Layout
		//		this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x;
		//		this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y;
		//		this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z;
		//#else
		//		// Column Major Memory Layout
		//		this->x = Col1; this->y = Col2; this->z = Col3;
		//#endif // !COL_MAJOR_MEMORY_LAYOUT
		this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x;
		this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y;
		this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z;
	}

	real3x3::real3x3(const real3x3& Arg) {
		memcpy(this->ptr, Arg.ptr, sizeof(real3x3));
	}

	real3x3& real3x3::operator=(const real3x3& Rhs) {
		memcpy(this->ptr, Rhs.ptr, sizeof(real3x3));
		return *this;
	}

	real real3x3::operator()(integer RowElement, integer ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
		return this->ptr[RowElement + ColumnElement * 3];
#else
		return this->ptr[RowElement * 3 + ColumnElement];
#endif // !COL_MAJOR_MEMORY_LAYOUT
	}

	real& real3x3::operator()(integer RowElement, integer ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
		return this->ptr[RowElement + ColumnElement * 3];
#else
		return this->ptr[RowElement * 3 + ColumnElement];
#endif // !COL_MAJOR_MEMORY_LAYOUT
	}

	real3x3 real3x3::operator-() const {
		real3x3 temp;
		for (integer i = 0; i < 3 * 3; i++) {
			temp.ptr[i] = -this->ptr[i];
		}
		return temp;
	}

	real3x3 real3x3::operator+(const real3x3& Rhs) const {
		real3x3 temp;
		for (integer i = 0; i < 3 * 3; i++) {
			temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
		}
		return temp;
	}

	real3x3 real3x3::operator-(const real3x3& Rhs) const {
		real3x3 temp;
		for (integer i = 0; i < 3 * 3; i++) {
			temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
		}
		return temp;
	}

	real3x3 real3x3::operator*(const real3x3& Rhs) const {
		real3x3 temp;
		for (integer i = 0; i < 3; i++) {
			for (integer j = 0; j < 3; j++) {
				for (integer k = 0; k < 3; k++) {
					temp(i, j) += (*this)(i, k) * Rhs(k, j);
				}
			}
		}
		return temp;
	}

	real3x3& real3x3::operator+=(const real3x3& Rhs) {
		*this = *this + Rhs;
		return *this;
	}

	real3x3& real3x3::operator-=(const real3x3& Rhs) {
		*this = *this - Rhs;
		return *this;
	}

	real3x3& real3x3::operator*=(const real3x3& Rhs) {
		*this = *this * Rhs;
		return *this;
	}

	real3 real3x3::operator*(const real3& Rhs) const {
		real3 temp;
		for (integer i = 0; i < 3; i++) {
			for (integer j = 0; j < 3; j++) {
				temp[i] += (*this)(i, j) * Rhs[j];
			}
		}
		return temp;
	}

	real3x3 real3x3::operator*(real Rhs) const {
		real3x3 temp;
		for (integer i = 0; i < 3 * 3; i++) {
			temp.ptr[i] = this->ptr[i] * Rhs;
		}
		return temp;
	}

	real3x3 real3x3::operator/(real Rhs) const {
		real3x3 temp;
		for (integer i = 0; i < 3 * 3; i++) {
			temp.ptr[i] = this->ptr[i] / Rhs;
		}
		return temp;
	}

	real2x2 real3x3::sub(integer RowElement, integer ColumnElement) const {
		real2x2 temp;
		for (integer i = 0; i < 2; i++) {
			for (integer j = 0; j < 2; j++) {
				if ((i < RowElement) && (j < ColumnElement)) {
					temp(i, j) = (*this)(i, j);
				}
				else if (i < RowElement) {
					temp(i, j) = (*this)(i, j + 1);
				}
				else if (j < ColumnElement) {
					temp(i, j) = (*this)(i + 1, j);
				}
				else {
					temp(i, j) = (*this)(i + 1, j + 1);
				}
			}
		}
		return temp;
	}

	void real3x3::setr(const real3& Row1, const real3& Row2, const real3& Row3) {
		this->xx = Row1.x; this->xy = Row1.y; this->xz = Row1.z;
		this->yx = Row2.x; this->yy = Row2.y; this->yz = Row2.z;
		this->zx = Row3.x; this->zy = Row3.y; this->zz = Row3.z;
	}

	void real3x3::setc(const real3& Col1, const real3& Col2, const real3& Col3) {
		this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x;
		this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y;
		this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z;
	}

	real3 operator*(const real3& Lhs, const real3x3& Rhs) {
		real3 temp;
		for (integer i = 0; i < 3; i++) {
			for (integer j = 0; j < 3; j++) {
				temp[i] += Lhs[j] * Rhs(j, i);
			}
		}
		return temp;
	}

	real3x3 operator*(real Lhs, const real3x3& Rhs) {
		return Rhs * Lhs;
	}

	real det(const real3x3& Arg) {
		real Determinant = 0.0;
		integer sign = 0;
		integer3 i;
		for (i.x = 0; i.x < 3; i.x++) {
			for (i.y = 0; i.y < 3; i.y++) {
				for (i.z = 0; i.z < 3; i.z++) {
					sign = levi_civita(3, i.x, i.y, i.z);
					if (sign == 0) continue;
					Determinant += ((real)sign) * (Arg(0, i.x) * Arg(1, i.y) * Arg(2, i.z));
				}
			}
		}
		return Determinant;
	}

	real tr(const real3x3& Arg) {
		return (Arg(0, 0) + Arg(1, 1) + Arg(2, 2));
	}

	real3x3 transpose(const real3x3& Arg) {
		real3x3 temp;
		for (integer i = 0; i < 3; i++) {
			for (integer j = 0; j < 3; j++) {
				temp(j, i) = Arg(i, j);
			}
		}
		return temp;
	}

	real3x3 inverse(const real3x3& Arg) {
		return (0.5 * (pow((tr(Arg)), 2.0) - tr(Arg * Arg)) * real3x3::I - Arg * tr(Arg) + Arg * Arg);
	}

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& Out, const real3x3& Arg) {
		for (integer i = 1; i <= 3; i++) {
			Out << "| ";
			for (integer j = 1; j <= 3; j++) {
				Out << Arg(i, j) << " ";
			}
			Out << "|" << std::endl;
		}
		return Out;
	}
#endif // MATH_ENABLE_IO

}
