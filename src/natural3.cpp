#include <geodesuka/core/math/vectors/natural3.h>

#include <limits.h>

#include <geodesuka/core/math/config.h>

namespace geodesuka::core::math {

	natural3 operator+(natural3 lhs, natural3 rhs) {
		natural3 temp = { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
		return temp;
	}

	natural3 operator-(natural3 lhs, natural3 rhs) {
		natural3 temp = { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
		return temp;
	}

	natural operator*(natural3 lhs, natural3 rhs) {
		return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
	}

	natural3 operator^(natural3 lhs, natural3 rhs) {
		natural3 temp = { lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x };
		return temp;
	}

	natural3 operator+(natural lhs, natural3 rhs) {
		natural3 temp = { lhs + rhs.x, lhs + rhs.y, lhs + rhs.z };
		return temp;
	}

	natural3 operator-(natural lhs, natural3 rhs) {
		natural3 temp = { lhs - rhs.x, lhs - rhs.y, lhs - rhs.z };
		return temp;
	}

	natural3 operator*(natural lhs, natural3 rhs) {
		natural3 temp = { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
		return temp;
	}

	natural3 operator/(natural lhs, natural3 rhs) {
		natural3 temp;

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

		return temp;
	}

	natural3 operator+(natural3 lhs, natural rhs) {
		natural3 temp = { lhs.x + rhs, lhs.y + rhs, lhs.z + rhs };
		return temp;
	}

	natural3 operator-(natural3 lhs, natural rhs) {
		natural3 temp = { lhs.x - rhs, lhs.y - rhs, lhs.z - rhs };
		return temp;
	}

	natural3 operator*(natural3 lhs, natural rhs) {
		natural3 temp = { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
		return temp;
	}

	natural3 operator/(natural3 lhs, natural rhs) {
		natural3 temp;
		if (rhs != 0u) {
			temp = { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
		}
		else {
			temp = { UINT_MAX, UINT_MAX, UINT_MAX };
		}
		return temp;
	}

}
