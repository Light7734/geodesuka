#pragma once
#ifndef GCLM_FRONT_UTIL_H
#define GCLM_FRONT_UTIL_H

#include <cmath>

/* This header configures usage. */
#include "../config.h"

/* Basic Internal Utility Functions */
#include "isupport.h"

/* -------------------- All Types Included here -------------------- */

/* Number Types */
//#include "boolean.h" Probably Dumb Type
#include "../numbers/natural.h"
#include "../numbers/integer.h"
//#include "rational.h" Dumb Type
#include "../numbers/real.h"
#include "../numbers/complex.h"
#include "../numbers/quaternion.h"

/* Built In Numerical Constants */
#include "../numbers/constants.h"

/* Vector Types */
#include "../vectors/natural2.h"
#include "../vectors/natural3.h"
#include "../vectors/natural4.h"
#include "../vectors/integer2.h"
#include "../vectors/integer3.h"
#include "../vectors/integer4.h"
#include "../vectors/real2.h"
#include "../vectors/real3.h"
#include "../vectors/real4.h"

/* Matrix Types */
/*
* When accessing matrix elements, the notation is
* math::realmxn A;
*
* Value = A(Row,Column);
*/
#include "../matrices/real2x2.h"
#include "../matrices/real2x3.h"
#include "../matrices/real2x4.h"
#include "../matrices/real3x2.h"
#include "../matrices/real3x3.h"
#include "../matrices/real3x4.h"
#include "../matrices/real4x2.h"
#include "../matrices/real4x3.h"
#include "../matrices/real4x4.h"

/* Inter-Matrix Multiplication */
#include "matrix_multiply.h"

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

namespace geodesuka {
	namespace core {
		namespace math {

			// This function generates a perspective matrix. Transforms to clip coordinates.
			real4x4 perspective(real FOV, real AspectRatio, real Near, real Far);
			real4x4 rotation(real Angle, real3 V);

		}
	}
}

#endif // !GCLM_FRONT_UTIL_H
