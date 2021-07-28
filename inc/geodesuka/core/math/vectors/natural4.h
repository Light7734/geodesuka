#pragma once
#ifndef NATURAL4_H
#define NATURAL4_H

#include "../config.h"

#include "../numbers/natural.h"

namespace geodesuka {
	namespace core {
		namespace math {

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
	}
}

#endif /* !NATURAL4_H */
