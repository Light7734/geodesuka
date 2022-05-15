#pragma once
#ifndef GEODESUKA_CORE_MATH_MATRIX_MULTIPLY_H
#define GEODESUKA_CORE_MATH_MATRIX_MULTIPLY_H
/*
* This file defines the various forms of matrix multiplication.
*/
#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"

/* Matrix Types */
#include "../matrix/float2x2.h"
#include "../matrix/float2x3.h"
#include "../matrix/float2x4.h"
#include "../matrix/float3x2.h"
#include "../matrix/float3x3.h"
#include "../matrix/float3x4.h"
#include "../matrix/float4x2.h"
#include "../matrix/float4x3.h"
#include "../matrix/float4x4.h"

//real2x2 operator*(real2x2 Lhs, real2x2 Rhs);
float2x3 operator*(float2x2 Lhs, float2x3 Rhs);
float2x4 operator*(float2x2 Lhs, float2x4 Rhs);

float2x2 operator*(float2x3 Lhs, float3x2 Rhs);
float2x3 operator*(float2x3 Lhs, float3x3 Rhs);
float2x4 operator*(float2x3 Lhs, float3x4 Rhs);

float2x2 operator*(float2x4 Lhs, float4x2 Rhs);
float2x3 operator*(float2x4 Lhs, float4x3 Rhs);
float2x4 operator*(float2x4 Lhs, float4x4 Rhs);



float3x2 operator*(float3x2 Lhs, float2x2 Rhs);
float3x3 operator*(float3x2 Lhs, float2x3 Rhs);
float3x4 operator*(float3x2 Lhs, float2x4 Rhs);

float3x2 operator*(float3x3 Lhs, float3x2 Rhs);
//real3x3 operator*(real3x3 Lhs, real3x3 Rhs);
float3x4 operator*(float3x3 Lhs, float3x4 Rhs);

float3x2 operator*(float3x4 Lhs, float4x2 Rhs);
float3x3 operator*(float3x4 Lhs, float4x3 Rhs);
float3x4 operator*(float3x4 Lhs, float4x4 Rhs);



float4x2 operator*(float4x2 Lhs, float2x2 Rhs);
float4x3 operator*(float4x2 Lhs, float2x3 Rhs);
float4x4 operator*(float4x2 Lhs, float2x4 Rhs);

float4x2 operator*(float4x3 Lhs, float3x2 Rhs);
float4x3 operator*(float4x3 Lhs, float3x3 Rhs);
float4x4 operator*(float4x3 Lhs, float3x4 Rhs);

float4x2 operator*(float4x4 Lhs, float4x2 Rhs);
float4x3 operator*(float4x4 Lhs, float4x3 Rhs);
//real4x4 operator*(real4x4 Lhs, real4x4 Rhs);

#endif // !GEODESUKA_CORE_MATH_MATRIX_MULTIPLY_H
