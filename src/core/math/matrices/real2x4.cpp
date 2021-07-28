#include <geodesuka/core/math/matrices/real2x4.h>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

namespace geodesuka {
	namespace core {
		namespace math {

			real real2x4::operator()(integer RowElement, integer ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				// Column Major Memory Layout
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real& real2x4::operator()(integer RowElement, integer ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				// Column Major Memory Layout
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real2x4 real2x4::operator-() const {
				real2x4 temp;
				for (integer i = 0; i < 2 * 4; i++) {
					temp.ptr[i] = this->ptr[i];
				}
				return temp;
			}

			real2x4 real2x4::operator+(const real2x4& Rhs) const {
				real2x4 temp;
				for (integer i = 0; i < 2 * 4; i++) {
					temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
				}
				return temp;
			}

			real2x4 real2x4::operator-(const real2x4& Rhs) const {
				real2x4 temp;
				for (integer i = 0; i < 2 * 4; i++) {
					temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
				}
				return temp;
			}

			real2x4& real2x4::operator+=(const real2x4& Rhs) {
				for (integer i = 0; i < 2 * 4; i++) {
					this->ptr[i] += Rhs.ptr[i];
				}
				return *this;
			}

			real2x4& real2x4::operator-=(const real2x4& Rhs) {
				for (integer i = 0; i < 2 * 4; i++) {
					this->ptr[i] += Rhs.ptr[i];
				}
				return *this;
			}

			real2 real2x4::operator*(const real4& Rhs) const {
				real2 temp;
				for (integer i = 0; i < 2; i++) {
					temp.ptr[i] = 0.0;
					for (integer j = 0; j < 4; j++) {
						temp.ptr[i] += (*this)(i + 1, j + 1) * Rhs.ptr[j];
					}
				}
				return temp;
			}

			real2x4 real2x4::operator*(real Rhs) const {
				real2x4 temp;
				for (integer i = 0; i < 2 * 4; i++) {
					temp.ptr[i] = this->ptr[i] * Rhs;
				}
				return temp;
			}

			real2x4 real2x4::operator/(real Rhs) const {
				real2x4 temp;
				for (integer i = 0; i < 2 * 4; i++) {
					temp.ptr[i] = this->ptr[i] / Rhs;
				}
				return temp;
			}

			void real2x4::setr(const real4& Row1, const real4& Row2) {
				this->xx = Row1.x; this->xy = Row1.y; this->xz = Row1.z; this->xt = Row1.t;
				this->yx = Row2.x; this->yy = Row2.y; this->yz = Row2.z; this->yt = Row2.t;
			}

			void real2x4::setc(const real2& Col1, const real2& Col2, const real2& Col3, const real2& Col4) {
				this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x; this->xt = Col4.x;
				this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y; this->yt = Col4.y;
			}

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real2x4& Arg)
			{
				for (integer i = 1; i <= 2; i++) {
					Out << "| ";
					for (integer j = 1; j <= 4; j++) {
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