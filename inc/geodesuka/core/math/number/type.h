#pragma once
#ifndef GEODESUKA_CORE_MATH_NUMBER_TYPE_H
#define GEODESUKA_CORE_MATH_NUMBER_TYPE_H

typedef unsigned char uchar, ubyte;
typedef unsigned short ushort;
typedef unsigned int uint;
//typedef unsigned long ulong;

typedef char byte;

//typedef ushort half;
//typedef float;
//typedef double;

namespace geodesuka::core::math {

	typedef unsigned int natural;
	typedef signed int integer;
	typedef float real;

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

#endif // !GEODESUKA_CORE_MATH_NUMBER_TYPE_H
