#pragma once
#ifndef GEODESUKA_CORE_MATH_NUMBER_H
#define GEODESUKA_CORE_MATH_NUMBER_H

#include "config.h"

// Includes number redefinition of types.
#include "number/type.h"
#include "number/complex.h"
#include "number/quaternion.h"

#include "number/constants.h"

namespace geodesuka::core::math {
	typedef uint natural;
	typedef int integer;
	typedef float real;
}

#endif // !GEODESUKA_CORE_MATH_NUMBER_H
