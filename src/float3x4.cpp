#include <geodesuka/core/math/matrix/float3x4.h>

#include <geodesuka/core/math/config.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/number/type.h>
#include <geodesuka/core/math/vector/float3.h>
#include <geodesuka/core/math/vector/float4.h>


//void float3x4::set_rows(const float4& Row1, const float4& Row2, const float4& Row3) {
//	this->x = Row1; this->y = Row2; this->z = Row3;
//}

//void float3x4::set_cols(const float3& Col1, const float3& Col2, const float3& Col3, const float3& Col4) {
//	this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x; this->xt = Col4.x;
//	this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y; this->yt = Col4.y;
//	this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z; this->zt = Col4.z;
//	//this->tx = Col1.t; this->ty = Col2.t; this->tz = Col3.t; this->tt = Col4.t;
//}


float float3x4::operator()(int RowElement, int ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	return this->aptr[RowElement - 1][ColumnElement - 1];
#else
	// Column Major Memory Layout
	return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
}

float& float3x4::operator()(int RowElement, int ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	// Row Major Memory Layout
	return this->aptr[RowElement - 1][ColumnElement - 1];
#else
	// Column Major Memory Layout
	return this->aptr[ColumnElement - 1][RowElement - 1];
#endif // !ROW_MAJOR_MEMORY_LAYOUT
}

float3x4 float3x4::operator-() const {
	float3x4 temp;
	for (int i = 0; i < 3 * 4; i++) {
		temp.ptr[i] = -this->ptr[i];
	}
	return temp;
}

float3x4 float3x4::operator+(const float3x4& Rhs) const {
	float3x4 temp;
	for (int i = 0; i < 3 * 4; i++) {
		temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
	}
	return temp;
}

float3x4 float3x4::operator-(const float3x4& Rhs) const {
	float3x4 temp;
	for (int i = 0; i < 3 * 4; i++) {
		temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
	}
	return temp;
}

float3x4& float3x4::operator+=(const float3x4& Rhs) {
	for (int i = 0; i < 3 * 4; i++) {
		this->ptr[i] += Rhs.ptr[i];
	}
	return *this;
}

float3x4& float3x4::operator-=(const float3x4& Rhs) {
	for (int i = 0; i < 3 * 4; i++) {
		this->ptr[i] -= Rhs.ptr[i];
	}
	return *this;
}

float3x4 float3x4::operator*(float Rhs) const {
	float3x4 temp;
	for (int i = 0; i < 3 * 4; i++) {
		temp.ptr[i] = this->ptr[i] * Rhs;
	}
	return temp;
}

float3x4 float3x4::operator/(float Rhs) const {
	float3x4 temp;
	for (int i = 0; i < 3 * 4; i++) {
		temp.ptr[i] = this->ptr[i] / Rhs;
	}
	return temp;
}

void float3x4::setr(const float4& Row1, const float4& Row2, const float4& Row3) {
	this->xx = Row1.x; this->xy = Row1.y; this->xz = Row1.z; this->xt = Row1.t;
	this->yx = Row2.x; this->yy = Row2.y; this->yz = Row2.z; this->yt = Row2.t;
	this->zx = Row3.x; this->zy = Row3.y; this->zz = Row3.z; this->zt = Row3.t;
}

void float3x4::setc(const float3& Col1, const float3& Col2, const float3& Col3, const float3& Col4) {
	this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x; this->xt = Col4.x;
	this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y; this->yt = Col4.y;
	this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z; this->zt = Col4.z;
}

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float3x4& Arg)
{
	for (int i = 1; i <= 3; i++) {
		Out << "| ";
		for (int j = 1; j <= 4; j++) {
			Out << Arg(i, j) << " ";
		}
		Out << "|" << std::endl;
	}
	return Out;
}
#endif // MATH_ENABLE_IO
