#pragma once
#ifndef NATURAL2_H
#define NATURAL2_H

#include "../config.h"

#include "../numbers/natural.h"

namespace geodesuka {
	namespace core {
		namespace math {

			struct natural2 {
				unsigned int x, y;
			};

			natural2 operator+(natural2 lhs, natural2 rhs);
			natural2 operator-(natural2 lhs, natural2 rhs);
			natural operator*(natural2 lhs, natural2 rhs);
			natural operator^(natural2 lhs, natural2 rhs);

			natural2 operator+(natural lhs, natural2 rhs);
			natural2 operator-(natural lhs, natural2 rhs);
			natural2 operator*(natural lhs, natural2 rhs);
			natural2 operator/(natural lhs, natural2 rhs);

			natural2 operator+(natural2 lhs, natural rhs);
			natural2 operator-(natural2 lhs, natural rhs);
			natural2 operator*(natural2 lhs, natural rhs);
			natural2 operator/(natural2 lhs, natural rhs);

		}
	}
}

#endif // !NATURAL2_H
