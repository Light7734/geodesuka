#pragma once
#ifndef GEODESUKA_CORE_MATH_VECTOR_H
#define GEODESUKA_CORE_MATH_VECTOR_H

#include "config.h"

#include "vector/ubyte2.h"
#include "vector/ubyte3.h"
#include "vector/ubyte4.h"

#include "vector/ushort2.h"
#include "vector/ushort3.h"
#include "vector/ushort4.h"

#include "vector/uint2.h"
#include "vector/uint3.h"
#include "vector/uint4.h"

#include "vector/byte2.h"
#include "vector/byte3.h"
#include "vector/byte4.h"

#include "vector/short2.h"
#include "vector/short3.h"
#include "vector/short4.h"

#include "vector/int2.h"
#include "vector/int3.h"
#include "vector/int4.h"

#include "vector/float2.h"
#include "vector/float3.h"
#include "vector/float4.h"

namespace geodesuka::core::math {
	typedef uint2 natural2;
	typedef uint3 natural3;
	typedef uint4 natural4;

	typedef int2 integer2;
	typedef int3 integer3;
	typedef int4 integer4;

	typedef float2 real2;
	typedef float3 real3;
	typedef float4 real4;
}

#endif // !GEODESUKA_CORE_MATH_VECTOR_H
