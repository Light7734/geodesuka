#pragma once
#ifndef GEODESUKA_CORE_MATH_NATURAL4_H
#define GEODESUKA_CORE_MATH_NATURAL4_H

#include "../config.h"

#include "../numbers/natural.h"

namespace geodesuka::core::math {

	struct natural4 {
		natural x, y, z, t;
	};

	natural4 operator+(natural4 lhs, natural4 rhs);
	natural4 operator-(natural4 lhs, natural4 rhs);
	natural operator*(natural4 lhs, natural4 rhs);

	natural4 operator+(natural lhs, natural4 rhs);
	natural4 operator-(natural lhs, natural4 rhs);
	natural4 operator*(natural lhs, natural4 rhs);
	natural4 operator/(natural lhs, natural4 rhs);

	natural4 operator+(natural4 lhs, natural rhs);
	natural4 operator-(natural4 lhs, natural rhs);
	natural4 operator*(natural4 lhs, natural rhs);
	natural4 operator/(natural4 lhs, natural rhs);

}

#endif // !GEODESUKA_CORE_MATH_NATURAL4_H
