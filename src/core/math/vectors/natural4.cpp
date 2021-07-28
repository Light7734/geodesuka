#include <geodesuka/core/math/vectors/natural4.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

#include <geodesuka/core/math/numbers/integer.h>

namespace geodesuka {
	namespace core {
		namespace math {

			natural4 operator+(natural4 lhs, natural4 rhs) {
				natural4 temp = {
					lhs.x + rhs.x,
					lhs.y + rhs.y,
					lhs.z + rhs.z,
					lhs.t + rhs.t
				};
				return temp;
			}

			natural4 operator-(natural4 lhs, natural4 rhs) {
				natural4 temp = {
					lhs.x - rhs.x,
					lhs.y - rhs.y,
					lhs.z - rhs.z,
					lhs.t - rhs.t
				};
				return temp;
			}

			natural operator*(natural4 lhs, natural4 rhs) {
				return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.t * rhs.t);
			}

			natural4 operator+(natural lhs, natural4 rhs) {
				natural4 temp = {
					lhs + rhs.x,
					lhs + rhs.y,
					lhs + rhs.z,
					lhs + rhs.t
				};
				return temp;
			}

			natural4 operator-(natural lhs, natural4 rhs) {
				natural4 temp = {
					lhs - rhs.x,
					lhs - rhs.y,
					lhs - rhs.z,
					lhs - rhs.t
				};
				return temp;
			}

			natural4 operator*(natural lhs, natural4 rhs) {
				natural4 temp = {
					lhs * rhs.x,
					lhs * rhs.y,
					lhs * rhs.z,
					lhs * rhs.t
				};
				return temp;
			}

			natural4 operator/(natural lhs, natural4 rhs) {
				natural4 temp;

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

				if (rhs.z != 0u) {
					temp.z = lhs / rhs.z;
				}
				else {
					temp.z = UINT_MAX;
				}

				if (rhs.t != 0u) {
					temp.t = lhs / rhs.t;
				}
				else {
					temp.t = UINT_MAX;
				}

				return temp;
			}

			natural4 operator+(natural4 lhs, natural rhs) {
				natural4 temp = {
					lhs.x + rhs,
					lhs.y + rhs,
					lhs.z + rhs,
					lhs.t + rhs
				};
				return temp;
			}

			natural4 operator-(natural4 lhs, natural rhs) {
				natural4 temp = {
					lhs.x - rhs,
					lhs.y - rhs,
					lhs.z - rhs,
					lhs.t - rhs
				};
				return temp;
			}

			natural4 operator*(natural4 lhs, natural rhs) {
				natural4 temp = {
					lhs.x * rhs,
					lhs.y * rhs,
					lhs.z * rhs,
					lhs.t * rhs
				};
				return temp;
			}

			natural4 operator/(natural4 lhs, natural rhs) {
				natural4 temp;
				if (rhs != 0u) {
					temp = {
						lhs.x / rhs,
						lhs.y / rhs,
						lhs.z / rhs,
						lhs.t / rhs
					};
				}
				else {
					temp = {
						UINT_MAX,
						UINT_MAX,
						UINT_MAX,
						UINT_MAX
					};
				}
				return temp;
			}

		}
	}
}
