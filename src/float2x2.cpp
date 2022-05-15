#include <geodesuka/core/math/matrix/float2x2.h>

#include <string.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/number/type.h>


const float2x2 float2x2::I = float2x2(
	1.0, 0.0,
	0.0, 1.0
);

float float2x2::operator()(int RowElement, int ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	return this->aptr[RowElement - 1][ColumnElement - 1];
#else
	// Column Major Memory Layout
	return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
}

float& float2x2::operator()(int RowElement, int ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	return this->aptr[RowElement - 1][ColumnElement - 1];
#else
	// Column Major Memory Layout
	return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
}

float2x2 float2x2::operator-() const {
	float2x2 temp;
	for (int i = 0; i < 2 * 2; i++) {
		temp.ptr[i] = -this->ptr[i];
	}
	return temp;
}

float2x2 float2x2::operator+(const float2x2& Rhs) const {
	float2x2 temp;
	for (int i = 0; i < 2 * 2; i++) {
		temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
	}
	return temp;
}

float2x2 float2x2::operator-(const float2x2& Rhs) const {
	float2x2 temp;
	for (int i = 0; i < 2 * 2; i++) {
		temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
	}
	return temp;
}

float2x2 float2x2::operator*(const float2x2& Rhs) const {
	float2x2 temp;
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= 2; j++) {
			for (int k = 1; k <= 2; k++) {
				temp(i, j) += (*this)(i, k) * Rhs(k, j);
			}
		}
	}
	return temp;
}

float2x2 float2x2::operator+=(const float2x2& Rhs) {
	*this = *this + Rhs;
	return *this;
}

float2x2 float2x2::operator-=(const float2x2& Rhs) {
	*this = *this - Rhs;
	return *this;
}

float2x2 float2x2::operator*=(const float2x2& Rhs) {
	*this = *this * Rhs;
	return *this;
}

float2 float2x2::operator*(const float2& Rhs) const {
	float2 temp;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			temp[i] += (*this)(i, j) * Rhs[j];
		}
	}
	return temp;
}

float2x2 float2x2::operator*(float Rhs) const {
	float2x2 temp;
	for (int i = 0; i < 2 * 2; i++) {
		temp.ptr[i] = this->ptr[i] * Rhs;
	}
	return temp;
}

float2x2 float2x2::operator/(float Rhs) const {
	float2x2 temp;
	for (int i = 0; i < 2 * 2; i++) {
		temp.ptr[i] = this->ptr[i] / Rhs;
	}
	return temp;
}

void float2x2::setr(const float2& Row1, const float2& Row2) {
	this->xx = Row1.x; this->xy = Row1.y;
	this->yx = Row2.x; this->yy = Row2.y;
}

void float2x2::setc(const float2& Col1, const float2& Col2) {
	this->xx = Col1.x; this->xy = Col2.x;
	this->yx = Col1.y; this->yy = Col2.y;
}

float2 operator*(const float2& Lhs, const float2x2& Rhs) {
	float2 temp;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			temp[i] += Rhs(j, i) * Lhs[j];
		}
	}
	return temp;
}

float2x2 operator*(float Lhs, const float2x2& Rhs) {
	return Rhs * Lhs;
}

float det(const float2x2& Arg) {
	return (Arg.xx * Arg.yy - Arg.yx * Arg.xy);
}

float tr(const float2x2& Arg) {
	return (Arg.xx + Arg.yy);
}

float2x2 transpose(const float2x2& Arg) {
	float2x2 temp;
	temp.xx = Arg.xx; temp.xy = Arg.yx;
	temp.yx = Arg.xy; temp.yy = Arg.yy;
	return temp;
}

float2x2 inverse(const float2x2& Arg) {
	return (
		float2x2(
			Arg.yy, -Arg.xy,
			-Arg.yx, Arg.xx
		) / det(Arg)
		);
}

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float2x2& Arg) {
	for (int i = 1; i <= 2; i++) {
		Out << "| ";
		for (int j = 1; j <= 2; j++) {
			Out << Arg(i, j) << " ";
		}
		Out << "|" << std::endl;
	}
	return Out;
}
#endif // MATH_ENABLE_IO
