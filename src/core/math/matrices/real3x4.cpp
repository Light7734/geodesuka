#include <geodesuka/core/math/matrices/real3x4.h>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/numbers/real.h>
#include <geodesuka/core/math/vectors/real3.h>
#include <geodesuka/core/math/vectors/real4.h>

namespace geodesuka {
	namespace core {
		namespace math {

			//void real3x4::set_rows(const real4& Row1, const real4& Row2, const real4& Row3) {
			//	this->x = Row1; this->y = Row2; this->z = Row3;
			//}

			//void real3x4::set_cols(const real3& Col1, const real3& Col2, const real3& Col3, const real3& Col4) {
			//	this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x; this->xt = Col4.x;
			//	this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y; this->yt = Col4.y;
			//	this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z; this->zt = Col4.z;
			//	//this->tx = Col1.t; this->ty = Col2.t; this->tz = Col3.t; this->tt = Col4.t;
			//}


			real real3x4::operator()(integer RowElement, integer ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				// Column Major Memory Layout
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real& real3x4::operator()(integer RowElement, integer ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
				// Row Major Memory Layout
				return this->aptr[RowElement - 1][ColumnElement - 1];
#else
				// Column Major Memory Layout
				return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
			}

			real3x4 real3x4::operator-() const {
				real3x4 temp;
				for (integer i = 0; i < 3 * 4; i++) {
					temp.ptr[i] = -this->ptr[i];
				}
				return temp;
			}

			real3x4 real3x4::operator+(const real3x4& Rhs) const {
				real3x4 temp;
				for (integer i = 0; i < 3 * 4; i++) {
					temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
				}
				return temp;
			}

			real3x4 real3x4::operator-(const real3x4& Rhs) const {
				real3x4 temp;
				for (integer i = 0; i < 3 * 4; i++) {
					temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
				}
				return temp;
			}

			real3x4& real3x4::operator+=(const real3x4& Rhs) {
				for (integer i = 0; i < 3 * 4; i++) {
					this->ptr[i] += Rhs.ptr[i];
				}
				return *this;
			}

			real3x4& real3x4::operator-=(const real3x4& Rhs) {
				for (integer i = 0; i < 3 * 4; i++) {
					this->ptr[i] -= Rhs.ptr[i];
				}
				return *this;
			}

			real3x4 real3x4::operator*(real Rhs) const {
				real3x4 temp;
				for (integer i = 0; i < 3 * 4; i++) {
					temp.ptr[i] = this->ptr[i] * Rhs;
				}
				return temp;
			}

			real3x4 real3x4::operator/(real Rhs) const {
				real3x4 temp;
				for (integer i = 0; i < 3 * 4; i++) {
					temp.ptr[i] = this->ptr[i] / Rhs;
				}
				return temp;
			}

			void real3x4::setr(const real4& Row1, const real4& Row2, const real4& Row3) {
				this->xx = Row1.x; this->xy = Row1.y; this->xz = Row1.z; this->xt = Row1.t;
				this->yx = Row2.x; this->yy = Row2.y; this->yz = Row2.z; this->yt = Row2.t;
				this->zx = Row3.x; this->zy = Row3.y; this->zz = Row3.z; this->zt = Row3.t;
			}

			void real3x4::setc(const real3& Col1, const real3& Col2, const real3& Col3, const real3& Col4) {
				this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x; this->xt = Col4.x;
				this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y; this->yt = Col4.y;
				this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z; this->zt = Col4.z;
			}

#ifdef MATH_ENABLE_IO
			std::ostream& operator<<(std::ostream& Out, const real3x4& Arg)
			{
				for (integer i = 1; i <= 3; i++) {
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
