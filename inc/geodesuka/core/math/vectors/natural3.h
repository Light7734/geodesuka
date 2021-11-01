#pragma once
#ifndef GEODESUKA_CORE_MATH_NATURAL3_H
#define GEODESUKA_CORE_MATH_NATURAL3_H

#include "../config.h"

#include "../numbers/natural.h"

namespace geodesuka::core::math {

	struct natural3 {
		unsigned int x, y, z;
	};

	natural3 operator+(natural3 lhs, natural3 rhs);
	natural3 operator-(natural3 lhs, natural3 rhs);
	natural operator*(natural3 lhs, natural3 rhs);
	natural3 operator^(natural3 lhs, natural3 rhs);

	natural3 operator+(natural lhs, natural3 rhs);
	natural3 operator-(natural lhs, natural3 rhs);
	natural3 operator*(natural lhs, natural3 rhs);
	natural3 operator/(natural lhs, natural3 rhs);

	natural3 operator+(natural3 lhs, natural rhs);
	natural3 operator-(natural3 lhs, natural rhs);
	natural3 operator*(natural3 lhs, natural rhs);
	natural3 operator/(natural3 lhs, natural rhs);

}

#endif // !GEODESUKA_CORE_MATH_NATURAL3_H
