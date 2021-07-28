#include <geodesuka/core/math/vectors/natural2.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/numbers/integer.h>

namespace geodesuka {
	namespace core {
		namespace math {

			natural2 operator+(natural2 lhs, natural2 rhs) {
				natural2 temp = { lhs.x + rhs.x, lhs.y + rhs.y };
				return temp;
			}

			natural2 operator-(natural2 lhs, natural2 rhs) {
				natural2 temp = { lhs.x - rhs.x, lhs.y - rhs.y };
				return temp;
			}

			natural operator*(natural2 lhs, natural2 rhs) {
				return (lhs.x * rhs.x + lhs.y * rhs.y);
			}

			natural operator^(natural2 lhs, natural2 rhs) {
				return (lhs.x * rhs.y - lhs.y * rhs.x);
			}

			natural2 operator+(natural lhs, natural2 rhs) {
				natural2 temp = { lhs + rhs.x, lhs + rhs.y };
				return temp;
			}

			natural2 operator-(natural lhs, natural2 rhs) {
				natural2 temp = { lhs - rhs.x, lhs - rhs.y };
				return temp;
			}

			natural2 operator*(natural lhs, natural2 rhs) {
				natural2 temp = { lhs * rhs.x, lhs * rhs.y };
				return temp;
			}

			natural2 operator/(natural lhs, natural2 rhs) {
				natural2 temp;

				if (rhs.x != 0u) {
					temp.x = lhs / rhs.x;
				}
				else {
					temp.x = UINT_MAX;
				}

				if (rhs.y != 0u) {
					temp.y = lhs / rhs.y;
				}
				else {
					temp.y = UINT_MAX;
				}

				return temp;
			}

			natural2 operator+(natural2 lhs, natural rhs) {
				natural2 temp = { lhs.x + rhs, lhs.y + rhs };
				return temp;
			}

			natural2 operator-(natural2 lhs, natural rhs) {
				natural2 temp = { lhs.x - rhs, lhs.y - rhs };
				return temp;
			}

			natural2 operator*(natural2 lhs, natural rhs) {
				natural2 temp = { lhs.x * rhs, lhs.y * rhs };
				return temp;
			}

			natural2 operator/(natural2 lhs, unsigned int rhs) {
				natural2 temp;
				if (rhs != 0u) {
					temp = { lhs.x / rhs, lhs.y / rhs };
				}
				else {
					temp = { UINT_MAX, UINT_MAX };
				}
				return temp;
			}

		}
	}
}
