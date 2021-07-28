#include <geodesuka/core/math/matrices/real2x2.h>

#include <string.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/numbers/real.h>

namespace geodesuka {
	namespace core {
		namespace math {

			const real2x2 real2x2::I = real2x2(
				1.0, 0.0,
				0.0, 1.0
			);

			real real2x2::operator()(integer RowElement, integer ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				// Column Major Memory Layout
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real& real2x2::operator()(integer RowElement, integer ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				// Column Major Memory Layout
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real2x2 real2x2::operator-() const {
				real2x2 temp;
				for (integer i = 0; i < 2 * 2; i++) {
					temp.ptr[i] = -this->ptr[i];
				}
				return temp;
			}

			real2x2 real2x2::operator+(const real2x2& Rhs) const {
				real2x2 temp;
				for (integer i = 0; i < 2 * 2; i++) {
					temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
				}
				return temp;
			}

			real2x2 real2x2::operator-(const real2x2& Rhs) const {
				real2x2 temp;
				for (integer i = 0; i < 2 * 2; i++) {
					temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
				}
				return temp;
			}

			real2x2 real2x2::operator*(const real2x2& Rhs) const {
				real2x2 temp;
				for (integer i = 1; i <= 2; i++) {
					for (integer j = 1; j <= 2; j++) {
						for (integer k = 1; k <= 2; k++) {
							temp(i, j) += (*this)(i, k) * Rhs(k, j);
						}
					}
				}
				return temp;
			}

			real2x2 real2x2::operator+=(const real2x2& Rhs) {
				*this = *this + Rhs;
				return *this;
			}

			real2x2 real2x2::operator-=(const real2x2& Rhs) {
				*this = *this - Rhs;
				return *this;
			}

			real2x2 real2x2::operator*=(const real2x2& Rhs) {
				*this = *this * Rhs;
				return *this;
			}

			real2 real2x2::operator*(const real2& Rhs) const {
				real2 temp;
				for (integer i = 0; i < 2; i++) {
					for (integer j = 0; j < 2; j++) {
						temp[i] += (*this)(i, j) * Rhs[j];
					}
				}
				return temp;
			}

			real2x2 real2x2::operator*(real Rhs) const {
				real2x2 temp;
				for (integer i = 0; i < 2 * 2; i++) {
					temp.ptr[i] = this->ptr[i] * Rhs;
				}
				return temp;
			}

			real2x2 real2x2::operator/(real Rhs) const {
				real2x2 temp;
				for (integer i = 0; i < 2 * 2; i++) {
					temp.ptr[i] = this->ptr[i] / Rhs;
				}
				return temp;
			}

			void real2x2::setr(const real2& Row1, const real2& Row2) {
				this->xx = Row1.x; this->xy = Row1.y;
				this->yx = Row2.x; this->yy = Row2.y;
			}

			void real2x2::setc(const real2& Col1, const real2& Col2) {
				this->xx = Col1.x; this->xy = Col2.x;
				this->yx = Col1.y; this->yy = Col2.y;
			}

			real2 operator*(const real2& Lhs, const real2x2& Rhs) {
				real2 temp;
				for (integer i = 0; i < 2; i++) {
					for (integer j = 0; j < 2; j++) {
						temp[i] += Rhs(j, i) * Lhs[j];
					}
				}
				return temp;
			}

			real2x2 operator*(real Lhs, const real2x2& Rhs) {
				return Rhs * Lhs;
			}

			real det(const real2x2& Arg) {
				return (Arg.xx * Arg.yy - Arg.yx * Arg.xy);
			}

			real tr(const real2x2& Arg) {
				return (Arg.xx + Arg.yy);
			}

			real2x2 transpose(const real2x2& Arg) {
				real2x2 temp;
				temp.xx = Arg.xx; temp.xy = Arg.yx;
				temp.yx = Arg.xy; temp.yy = Arg.yy;
				return temp;
			}

			real2x2 inverse(const real2x2& Arg) {
				return (
					real2x2(
						Arg.yy, -Arg.xy,
						-Arg.yx, Arg.xx
					) / det(Arg)
					);
			}

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real2x2& Arg) {
				for (integer i = 1; i <= 2; i++) {
					Out << "| ";
					for (integer j = 1; j <= 2; j++) {
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
