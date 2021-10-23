#include <geodesuka/core/math/matrices/real2x3.h>

#include <string.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/vectors/real2.h>
#include <geodesuka/core/math/vectors/real3.h>
#include <geodesuka/core/math/vectors/real4.h>

namespace geodesuka {
	namespace core {
		namespace math {

			real2x3::real2x3(const real2x3& Arg) {
				memcpy(this->ptr, Arg.ptr, 2 * 3 * sizeof(real));
			}

			real2x3& real2x3::operator=(const real2x3& Rhs) {
				memcpy(this->ptr, Rhs.ptr, 2 * 3 * sizeof(real));
				return *this;
			}

			real real2x3::operator()(integer RowElement, integer ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				// Column Major Memory Layout
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real& real2x3::operator()(integer RowElement, integer ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				// Column Major Memory Layout
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real2x3 real2x3::operator-() const {
				real2x3 temp;
				for (integer i = 0; i < 2 * 3; i++) {
					temp.ptr[i] = -this->ptr[i];
				}
				return temp;
			}

			real2x3 real2x3::operator+(const real2x3& Rhs) const {
				real2x3 temp;
				for (integer i = 0; i < 2 * 3; i++) {
					temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
				}
				return temp;
			}

			real2x3 real2x3::operator-(const real2x3& Rhs) const {
				real2x3 temp;
				for (integer i = 0; i < 2 * 3; i++) {
					temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
				}
				return temp;
			}

			real2x3& real2x3::operator+=(const real2x3& Rhs) {
				for (integer i = 0; i < 2 * 3; i++) {
					this->ptr[i] += Rhs.ptr[i];
				}
				return *this;
			}

			real2x3& real2x3::operator-=(const real2x3& Rhs) {
				for (integer i = 0; i < 2 * 3; i++) {
					this->ptr[i] -= Rhs.ptr[i];
				}
				return *this;
			}

			real2 real2x3::operator*(const real3& Rhs) const {
				real2 temp;
				for (integer i = 0; i < 2; i++) {
					temp[i] = 0.0;
					for (integer j = 0; j < 3; j++) {
						temp[i] += (*this)(i, j) * Rhs[j];
					}
				}
				return temp;
			}

			real2x3 real2x3::operator*(real Rhs) const {
				real2x3 temp;
				for (integer i = 0; i < 2 * 3; i++) {
					temp.ptr[i] = this->ptr[i] * Rhs;
				}
				return temp;
			}

			real2x3 real2x3::operator/(real Rhs) const {
				real2x3 temp;
				for (integer i = 0; i < 2 * 3; i++) {
					temp.ptr[i] = this->ptr[i] / Rhs;
				}
				return temp;
			}

			void real2x3::setr(const real3& Row1, const real3& Row2) {
				this->xx = Row1.x; this->xy = Row1.y; this->xz = Row1.z;
				this->yx = Row2.x; this->yy = Row2.y; this->yz = Row2.z;
			}

			void real2x3::setc(const real2& Col1, const real2& Col2, const real2& Col3) {
				this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x;
				this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y;
			}

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real2x3& Arg) {
				for (integer i = 1; i <= 2; i++) {
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
	}
}
