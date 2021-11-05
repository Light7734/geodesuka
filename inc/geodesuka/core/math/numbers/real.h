#pragma once
#ifndef GEODESUKA_CORE_MATH_REAL_H
#define GEODESUKA_CORE_MATH_REAL_H

#include "../config.h"

#ifdef REAL_TYPE_HALF
	#define REAL_TYPE half?
#endif // REAL_TYPE_HALF

#ifdef REAL_TYPE_FLOAT
	#define REAL_TYPE float
#endif // REAL_TYPE_FLOAT

#ifdef REAL_TYPE_DOUBLE
	#define REAL_TYPE double 
#endif // REAL_TYPE_DOUBLE

namespace geodesuka::core::math {

	typedef REAL_TYPE real;

	// Apparently windows has their own definitions. 
#ifndef _WINDOWS_
	real min(real aA, real aB);
	real max(real aA, real aB);
#endif

	real ln(real Arg);
	real log(real Base, real RetVal);
	//real atan(real ArgY, real ArgX);

	real deg2rad(real Arg);
	real rad2deg(real Arg);

}

#endif // !GEODESUKA_CORE_MATH_REAL_H
