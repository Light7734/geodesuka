#include <geodesuka/core/math/matrix/float3x3.h>

#include <string.h>

#include <cmath>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/util/isupport.h>

#ifdef MATH_ENABLE_IO
#include <iostream>
#endif // MATH_ENABLE_IO

#include <geodesuka/core/math/number/type.h>
#include <geodesuka/core/math/vector/int2.h>
#include <geodesuka/core/math/vector/int3.h>

#include <geodesuka/core/math/vector/float2.h>
#include <geodesuka/core/math/vector/float3.h>
#include <geodesuka/core/math/vector/float4.h>


const float3x3 float3x3::I = float3x3(
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0
);

float3x3::float3x3(const float3& Col1, const float3& Col2, const float3& Col3) {
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

float3x3::float3x3(const float3x3& Arg) {
	memcpy(this->ptr, Arg.ptr, sizeof(float3x3));
}

float3x3& float3x3::operator=(const float3x3& Rhs) {
	memcpy(this->ptr, Rhs.ptr, sizeof(float3x3));
	return *this;
}

float float3x3::operator()(int RowElement, int ColumnElement) const {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	return this->ptr[RowElement + ColumnElement * 3];
#else
	return this->ptr[RowElement * 3 + ColumnElement];
#endif // !COL_MAJOR_MEMORY_LAYOUT
}

float& float3x3::operator()(int RowElement, int ColumnElement) {
#ifdef ROW_MAJOR_MEMORY_LAYOUT
	return this->ptr[RowElement + ColumnElement * 3];
#else
	return this->ptr[RowElement * 3 + ColumnElement];
#endif // !COL_MAJOR_MEMORY_LAYOUT
}

float3x3 float3x3::operator-() const {
	float3x3 temp;
	for (int i = 0; i < 3 * 3; i++) {
		temp.ptr[i] = -this->ptr[i];
	}
	return temp;
}

float3x3 float3x3::operator+(const float3x3& Rhs) const {
	float3x3 temp;
	for (int i = 0; i < 3 * 3; i++) {
		temp.ptr[i] = this->ptr[i] + Rhs.ptr[i];
	}
	return temp;
}

float3x3 float3x3::operator-(const float3x3& Rhs) const {
	float3x3 temp;
	for (int i = 0; i < 3 * 3; i++) {
		temp.ptr[i] = this->ptr[i] - Rhs.ptr[i];
	}
	return temp;
}

float3x3 float3x3::operator*(const float3x3& Rhs) const {
	float3x3 temp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				temp(i, j) += (*this)(i, k) * Rhs(k, j);
			}
		}
	}
	return temp;
}

float3x3& float3x3::operator+=(const float3x3& Rhs) {
	*this = *this + Rhs;
	return *this;
}

float3x3& float3x3::operator-=(const float3x3& Rhs) {
	*this = *this - Rhs;
	return *this;
}

float3x3& float3x3::operator*=(const float3x3& Rhs) {
	*this = *this * Rhs;
	return *this;
}

float3 float3x3::operator*(const float3& Rhs) const {
	float3 temp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp[i] += (*this)(i, j) * Rhs[j];
		}
	}
	return temp;
}

float3x3 float3x3::operator*(float Rhs) const {
	float3x3 temp;
	for (int i = 0; i < 3 * 3; i++) {
		temp.ptr[i] = this->ptr[i] * Rhs;
	}
	return temp;
}

float3x3 float3x3::operator/(float Rhs) const {
	float3x3 temp;
	for (int i = 0; i < 3 * 3; i++) {
		temp.ptr[i] = this->ptr[i] / Rhs;
	}
	return temp;
}

float2x2 float3x3::sub(int RowElement, int ColumnElement) const {
	float2x2 temp;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
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

void float3x3::setr(const float3& Row1, const float3& Row2, const float3& Row3) {
	this->xx = Row1.x; this->xy = Row1.y; this->xz = Row1.z;
	this->yx = Row2.x; this->yy = Row2.y; this->yz = Row2.z;
	this->zx = Row3.x; this->zy = Row3.y; this->zz = Row3.z;
}

void float3x3::setc(const float3& Col1, const float3& Col2, const float3& Col3) {
	this->xx = Col1.x; this->xy = Col2.x; this->xz = Col3.x;
	this->yx = Col1.y; this->yy = Col2.y; this->yz = Col3.y;
	this->zx = Col1.z; this->zy = Col2.z; this->zz = Col3.z;
}

float3 operator*(const float3& Lhs, const float3x3& Rhs) {
	float3 temp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp[i] += Lhs[j] * Rhs(j, i);
		}
	}
	return temp;
}

float3x3 operator*(float Lhs, const float3x3& Rhs) {
	return Rhs * Lhs;
}

float det(const float3x3& Arg) {
	float Determinant = 0.0;
	int sign = 0;
	int3 i;
	for (i.x = 0; i.x < 3; i.x++) {
		for (i.y = 0; i.y < 3; i.y++) {
			for (i.z = 0; i.z < 3; i.z++) {
				sign = levi_civita(3, i.x, i.y, i.z);
				if (sign == 0) continue;
				Determinant += ((float)sign) * (Arg(0, i.x) * Arg(1, i.y) * Arg(2, i.z));
			}
		}
	}
	return Determinant;
}

float tr(const float3x3& Arg) {
	return (Arg(0, 0) + Arg(1, 1) + Arg(2, 2));
}

float3x3 transpose(const float3x3& Arg) {
	float3x3 temp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp(j, i) = Arg(i, j);
		}
	}
	return temp;
}

float3x3 inverse(const float3x3& Arg) {
	return (0.5 * (pow((tr(Arg)), 2.0) - tr(Arg * Arg)) * float3x3::I - Arg * tr(Arg) + Arg * Arg);
}

#ifdef MATH_ENABLE_IO
std::ostream& operator<<(std::ostream& Out, const float3x3& Arg) {
	for (int i = 1; i <= 3; i++) {
		Out << "| ";
		for (int j = 1; j <= 3; j++) {
			Out << Arg(i, j) << " ";
		}
		Out << "|" << std::endl;
	}
	return Out;
}
#endif // MATH_ENABLE_IO
