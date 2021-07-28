#include <geodesuka/core/math/matrices/real4x4.h>

#include <string.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/util/isupport.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/numbers/integer.h>
#include <geodesuka/core/math/vectors/integer2.h>
#include <geodesuka/core/math/vectors/integer3.h>
#include <geodesuka/core/math/vectors/integer4.h>

#include <geodesuka/core/math/numbers/real.h>
#include <geodesuka/core/math/vectors/real2.h>
#include <geodesuka/core/math/vectors/real3.h>
#include <geodesuka/core/math/vectors/real4.h>

#include <geodesuka/core/math/matrices/real2x2.h>
#include <geodesuka/core/math/matrices/real3x3.h>

namespace geodesuka {
	namespace core {
		namespace math {

			const real4x4 real4x4::I = real4x4(
				1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0
			);

			//real4x4::real4x4(const real4x4& Arg) {
			//	memcpy(this->ptr, Arg.ptr, sizeof(real4x4));
			//}

			//real4x4& real4x4::operator=(const real4x4& Rhs) {
			//	memcpy(this->ptr, Rhs.ptr, sizeof(real4x4));
			//	return *this;
			//}

			real real4x4::operator()(integer RowElement, integer ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real& real4x4::operator()(integer RowElement, integer ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real4x4 real4x4::operator-() const {
				real4x4 temp;
				for (integer i = 0; i < 4 * 4; i++) {
					temp.ptr[i] = -this->ptr[i];
				}
				return temp;
			}

			real4x4 real4x4::operator+(const real4x4& Rhs) const {
				real4x4 temp;
				for (integer i = 0; i < 4 * 4; i++) {
					temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
				}
				return temp;
			}

			real4x4 real4x4::operator-(const real4x4& Rhs) const {
				real4x4 temp;
				for (integer i = 0; i < 4 * 4; i++) {
					temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
				}
				return temp;
			}

			real4x4 real4x4::operator*(const real4x4& Rhs) const {
				// C = A * B ---> c_ij = a_ik * b_kj;
				real4x4 temp;
				for (integer i = 1; i <= 4; i++) {
					for (integer j = 1; j <= 4; j++) {
						for (integer k = 1; k <= 4; k++) {
							temp(i, j) += (*this)(i, k) * Rhs(k, j);
						}
					}
				}
				return temp;
			}

			real4x4& real4x4::operator+=(const real4x4& Rhs) {
				for (integer i = 0; i < 4 * 4; i++) {
					this->ptr[i] += Rhs.ptr[i];
				}
				return *this;
			}

			real4x4& real4x4::operator-=(const real4x4& Rhs) {
				for (integer i = 0; i < 4 * 4; i++) {
					this->ptr[i] -= Rhs.ptr[i];
				}
				return *this;
			}

			real4x4& real4x4::operator*=(const real4x4& Rhs) {
				*this = *this * Rhs;
				return *this;
			}

			real4 real4x4::operator*(const real4& Rhs) const {
				real4 temp;
				for (integer i = 0; i < 4; i++) {
					for (integer j = 0; j < 4; j++) {
						temp[i] += (*this)(i + 1, j + 1) * Rhs[j];
					}
				}
				return temp;
			}

			real4x4 real4x4::operator*(real Rhs) const {
				real4x4 temp;
				for (integer i = 0; i < 4 * 4; i++) {
					temp.ptr[i] = this->ptr[i] * Rhs;
				}
				return temp;
			}

			real4x4 real4x4::operator/(real Rhs) const {
				real4x4 temp;
				for (integer i = 0; i < 4 * 4; i++) {
					temp.ptr[i] = this->ptr[i] / Rhs;
				}
				return temp;
			}

			real3x3 real4x4::sub(integer RowElement, integer ColumnElement) const {
				real3x3 temp;
				for (integer i = 0; i < 3; i++) {
					for (integer j = 0; j < 3; j++) {
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

			void real4x4::setr(const real4& Row1, const real4& Row2, const real4& Row3, const real4& Row4) {
				this->xx = Row1.x; this->xy = Row1.y; this->xz = Row1.z; this->xt = Row1.t;
				this->yx = Row2.x; this->yy = Row2.y; this->yz = Row2.z; this->yt = Row2.t;
				this->zx = Row3.x; this->zy = Row3.y; this->zz = Row3.z; this->zt = Row3.t;
				this->tx = Row4.x; this->ty = Row4.y; this->tz = Row4.z; this->tt = Row4.t;
			}

			void real4x4::setc(const real4& Col1, const real4& Col2, const real4& Col3, const real4& Col4) {
				this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x; this->xt = Col4.x;
				this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y; this->yt = Col4.y;
				this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z; this->zt = Col4.z;
				this->tx = Col1.t; this->ty = Col2.t; this->tz = Col3.t; this->tt = Col4.t;
			}

			real4 operator*(const real4& Lhs, const real4x4& Rhs) {
				real4 temp;
				for (integer i = 0; i < 4; i++) {
					for (integer j = 0; j < 4; j++) {
						temp[i] += Lhs[j] * Rhs(j, i);
					}
				}
				return temp;
			}

			real4x4 operator*(real Lhs, const real4x4& Rhs) {
				return Rhs * Lhs;
			}

			real det(const real4x4& Arg) {
				real Determinant = 0.0;
				integer sign = 0;
				integer4 i;
				for (i.x = 0; i.x < 4; i.x++) {
					for (i.y = 0; i.y < 4; i.y++) {
						for (i.z = 0; i.z < 4; i.z++) {
							for (i.t = 0; i.t < 4; i.t++) {
								sign = levi_civita(4, i.x, i.y, i.z, i.t);
								if (sign == 0) continue;
								Determinant += ((real)sign) * (Arg(0, i.x) * Arg(1, i.y) * Arg(2, i.z) * Arg(3, i.t));
							}
						}
					}
				}
				return Determinant;
			}

			real tr(const real4x4& Arg) {
				return (Arg(0, 0) + Arg(1, 1) + Arg(2, 2) + Arg(3, 3));
			}

			real4x4 transpose(const real4x4& arg) {
				real4x4 temp;
				for (integer i = 0; i < 4; i++) {
					for (integer j = 0; j < 4; j++) {
						temp(j, i) = arg(i, j);
					}
				}
				return temp;
			}

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real4x4& Arg) {
				for (integer i = 1; i <= 4; i++) {
					Out << "| ";
					for (integer j = 1; j <= 4; j++) {
						if (Arg(i, j) >= 0) {
							Out << " ";
						}
						Out << Arg(i, j) << " ";
					}
					Out << "|" << std::endl;
				}
				return Out;
			}
#endif // MATH_ENABLE_IO

		}
	}
}
