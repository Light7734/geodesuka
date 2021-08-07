#pragma once
#ifndef GEODESUKA_CORE_MATH_H
#define GEODESUKA_CORE_MATH_H

/*\\ ---------------------------------------- gclm.h ---------------------------------------- \\//

Vector Notation:
	Vectors are to be treated as column vectors, but there is flexibility in left multiplication
	where the vector will serve as a row vector

Matrix Notation:
	Memory Layout of these objects is by default column major, define ROW_MAJOR_MEMORY_LAYOUT in mconfig.h
	if row major memory layout is preferred.
	Row Count: M
	Column Count: N
	realMxN is a M x N matrix (aka real[ROWS]x[COLUMNS])

TODO List:
	

//\\ ---------------------------------------- gclm.h ---------------------------------------- \\*/

#include <cmath>

/* This header configures usage. */
#include "config.h"

/* Basic Internal Utility Functions */
#include "util/isupport.h"

/* -------------------- All Types Included here -------------------- */

/* Number Types */
#include "numbers/boolean.h"
#include "numbers/natural.h"
#include "numbers/integer.h"
//#include "rational.h" Dumb Type
#include "numbers/real.h"
#include "numbers/complex.h"
#include "numbers/quaternion.h"

/* Built In Numerical Constants */
#include "numbers/constants.h"

/* Vector Types */
#include "vectors/natural2.h"
#include "vectors/natural3.h"
#include "vectors/natural4.h"

#include "vectors/integer2.h"
#include "vectors/integer3.h"
#include "vectors/integer4.h"

#include "vectors/real2.h"
#include "vectors/real3.h"
#include "vectors/real4.h"

/* Matrix Types */
/*
* When accessing matrix elements, the notation is 
* math::realmxn A;
* 
* Value = A(Row,Column);
*/
#include "matrices/real2x2.h"
#include "matrices/real2x3.h"
#include "matrices/real2x4.h"
#include "matrices/real3x2.h"
#include "matrices/real3x3.h"
#include "matrices/real3x4.h"
#include "matrices/real4x2.h"
#include "matrices/real4x3.h"
#include "matrices/real4x4.h"

/* Inter-Matrix Multiplication */
#include "util/matrix_multiply.h"

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

/* -------------------- Extended Functions -------------------- */

/* Utility Functions */
#include "util/fsupport.h"

#endif // !GEODESUKA_CORE_MATH_H
