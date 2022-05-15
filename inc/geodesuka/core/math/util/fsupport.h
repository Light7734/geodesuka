#pragma once
#ifndef GEODESUKA_CORE_MATH_GCLM_FRONT_UTIL_H
#define GEODESUKA_CORE_MATH_GCLM_FRONT_UTIL_H

#include <cmath>

/* This header configures usage. */
#include "../config.h"

/* Basic Internal Utility Functions */
#include "isupport.h"

/* -------------------- All Types Included here -------------------- */

#include "../number/type.h"

#include "../number/complex.h"
#include "../number/quaternion.h"

/* Built In Numerical Constants */
#include "../number/constants.h"

/* Vector Types */
#include "../vector/uint2.h"
#include "../vector/uint3.h"
#include "../vector/uint4.h"
#include "../vector/int2.h"
#include "../vector/int3.h"
#include "../vector/int4.h"
#include "../vector/float2.h"
#include "../vector/float3.h"
#include "../vector/float4.h"

/* Matrix Types */
/*
* When accessing matrix elements, the notation is
* math::realmxn A;
*
* Value = A(Row,Column);
*/
#include "../matrix/float2x2.h"
#include "../matrix/float2x3.h"
#include "../matrix/float2x4.h"
#include "../matrix/float3x2.h"
#include "../matrix/float3x3.h"
#include "../matrix/float3x4.h"
#include "../matrix/float4x2.h"
#include "../matrix/float4x3.h"
#include "../matrix/float4x4.h"

/* Inter-Matrix Multiplication */
#include "../matrix/multiply.h"

/* Matrix Multiplication Functions */
/* Scalar Field Types */
//#include "R1.h"
//#include "R2.h"
//#include "R3.h"
//#include "R4.h"

/* Vector Field Types */
//#include "real2_field.h"
//#include "real3_field.h"
//#include "real4_field.h"

/*
* This library was created to be useful for graphics programming.
*/

namespace geodesuka::core::math {

	// This function generates a perspective matrix. Transforms to clip coordinates.
	float4x4 perspective(real FOV, real AspectRatio, real Near, real Far);
	float4x4 rotation(real Angle, float3 V);

}

#endif // !GEODESUKA_CORE_MATH_GCLM_FRONT_UTIL_H
