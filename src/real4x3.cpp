#include <geodesuka/core/math/matrices/real4x3.h>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

namespace geodesuka::core::math {

	real real4x3::operator()(integer RowElement, integer ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
		// Row Major Memory Layout
		return this->aptr[RowElement - 1][ColumnElement - 1];
#else
		// Column Major Memory Layout
		return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
	}

	real& real4x3::operator()(integer RowElement, integer ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
		// Row Major Memory Layout
		return this->aptr[RowElement - 1][ColumnElement - 1];
#else
		// Column Major Memory Layout
		return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
	}

	real4x3 real4x3::operator-() const {
		real4x3 temp;
		for (integer i = 0; i < 4 * 3; i++) {
			temp.ptr[i] = -this->ptr[i];
		}
		return temp;
	}

	real4x3 real4x3::operator+(const real4x3& Rhs) const {
		real4x3 temp;
		for (integer i = 0; i < 4 * 3; i++) {
			temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
		}
		return temp;
	}

	real4x3 real4x3::operator-(const real4x3& Rhs) const {
		real4x3 temp;
		for (integer i = 0; i < 4 * 3; i++) {
			temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
		}
		return temp;
	}

	real4x3& real4x3::operator+=(const real4x3& Rhs) {
		for (integer i = 0; i < 4 * 3; i++) {
			this->ptr[i] += Rhs.ptr[i];
		}
		return *this;
	}

	real4x3& real4x3::operator-=(const real4x3& Rhs) {
		for (integer i = 0; i < 4 * 3; i++) {
			this->ptr[i] -= Rhs.ptr[i];
		}
		return *this;
	}

	real4 real4x3::operator*(const real3& Rhs) const {
		return real4();
	}

	real4x3 real4x3::operator*(real Rhs) const {
		real4x3 temp;
		for (integer i = 0; i < 4 * 3; i++) {
			temp.ptr[i] = this->ptr[i] * Rhs;
		}
		return temp;
	}

	real4x3 real4x3::operator/(real Rhs) const {
		real4x3 temp;
		for (integer i = 0; i < 4 * 3; i++) {
			temp.ptr[i] = this->ptr[i] / Rhs;
		}
		return temp;
	}

	void real4x3::setr(const real3& Row1, const real3& Row2, const real3& Row3, const real3& Row4) {
		this->xx = Row1.x; this->xy = Row1.y; this->xz = Row1.z;
		this->yx = Row2.x; this->yy = Row2.y; this->yz = Row2.z;
		this->zx = Row3.x; this->zy = Row3.y; this->zz = Row3.z;
		this->tx = Row4.x; this->ty = Row4.y; this->tz = Row4.z;
	}

	void real4x3::setc(const real4& Col1, const real4& Col2, const real4& Col3) {
		this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x;
		this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y;
		this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z;
		this->tx = Col1.t; this->ty = Col2.t; this->tz = Col3.t;
	}

#ifdef MATH_ENABLE_IO
	std::ostream& operator<<(std::ostream& Out, const real4x3& Arg) {
		for (integer i = 1; i <= 4; i++) {
			Out << "| ";
			for (integer j = 1; j <= 3; j++) {
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
