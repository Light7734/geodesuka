#include <geodesuka/core/math/matrix/float4x2.h>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO


float float4x2::operator()(int RowElement, int ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	return this->aptr[RowElement - 1][ColumnElement - 1];
#else
	// Column Major Memory Layout
	return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
}

float& float4x2::operator()(int RowElement, int ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	return this->aptr[RowElement - 1][ColumnElement - 1];
#else
	// Column Major Memory Layout
	return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
}

float4x2 float4x2::operator-() const {
	float4x2 temp;
	for (int i = 0; i < 4 * 2; i++) {
		temp.ptr[i] = -this->ptr[i];
	}
	return temp;
}

float4x2 float4x2::operator+(const float4x2& Rhs) const {
	float4x2 temp;
	for (int i = 0; i < 4 * 2; i++) {
		temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
	}
	return temp;
}

float4x2 float4x2::operator-(const float4x2& Rhs) const {
	float4x2 temp;
	for (int i = 0; i < 4 * 2; i++) {
		temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
	}
	return temp;
}

float4x2& float4x2::operator+=(const float4x2& Rhs) {
	for (int i = 0; i < 4 * 2; i++) {
		this->ptr[i] += Rhs.ptr[i];
	}
	return *this;
}

float4x2& float4x2::operator-=(const float4x2& Rhs) {
	for (int i = 0; i < 4 * 2; i++) {
		this->ptr[i] -= Rhs.ptr[i];
	}
	return *this;
}

float4x2 float4x2::operator*(float Rhs) const {
	float4x2 temp;
	for (int i = 0; i < 4 * 2; i++) {
		temp.ptr[i] = this->ptr[i] * Rhs;
	}
	return temp;
}

float4x2 float4x2::operator/(float Rhs) const {
	float4x2 temp;
	for (int i = 0; i < 4 * 2; i++) {
		temp.ptr[i] = this->ptr[i] / Rhs;
	}
	return temp;
}

void float4x2::setr(const float2& Row1, const float2& Row2, const float2& Row3, const float2& Row4) {
	this->xx = Row1.x; this->xy = Row1.y;
	this->yx = Row2.x; this->yy = Row2.y;
	this->zx = Row3.x; this->zy = Row3.y;
	this->tx = Row4.x; this->ty = Row4.y;
}

void float4x2::setc(const float4& Col1, const float4& Col2) {
	this->xx = Col1.x; this->xy = Col2.x;
	this->yx = Col1.y; this->yy = Col2.y;
	this->zx = Col1.z; this->zy = Col2.z;
	this->tx = Col1.t; this->ty = Col2.t;
}

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float4x2& Arg) {
	for (int i = 1; i <= 4; i++) {
		Out << "| ";
		for (int j = 1; j <= 2; j++) {
			Out << Arg(i, j) << " ";
		}
		Out << "|" << std::endl;
	}
	return Out;
}
#endif // MATH_ENABLE_IO
