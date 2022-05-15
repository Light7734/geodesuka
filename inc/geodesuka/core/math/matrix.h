#pragma once
#ifndef GEODESUKA_CORE_MATH_MATRIX_H
#define GEODESUKA_CORE_MATH_MATRIX_H

#include "config.h"

#include "matrix/float2x2.h"
#include "matrix/float2x3.h"
#include "matrix/float2x4.h"
#include "matrix/float3x2.h"
#include "matrix/float3x3.h"
#include "matrix/float3x4.h"
#include "matrix/float4x2.h"
#include "matrix/float4x3.h"
#include "matrix/float4x4.h"

//#include "matrix/double2x2.h"
//#include "matrix/double2x3.h"
//#include "matrix/double2x4.h"
//#include "matrix/double3x2.h"
//#include "matrix/double3x3.h"
//#include "matrix/double3x4.h"
//#include "matrix/double4x2.h"
//#include "matrix/double4x3.h"
//#include "matrix/double4x4.h"

#include "matrix/multiply.h"

namespace geodesuka::core::math {
	typedef float2x2 real2x2;
	typedef float2x3 real2x3;
	typedef float2x4 real2x4;
	typedef float3x2 real3x2;
	typedef float3x3 real3x3;
	typedef float3x4 real3x4;
	typedef float4x2 real4x2;
	typedef float4x3 real4x3;
	typedef float4x4 real4x4;
}

#endif // !GEODESUKA_CORE_MATH_MATRIX_H
