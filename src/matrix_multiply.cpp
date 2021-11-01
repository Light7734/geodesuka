#include <geodesuka/core/math/util/matrix_multiply.h>

//tex:
// Matrix Multiplication
// $$C = AB$$
// $$ c_{ij} = \sum_{k} a_{ik} b_{kj} $$

namespace geodesuka::core::math {

	real2x3 operator*(real2x2 Lhs, real2x3 Rhs) {
		real2x3 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real2x4 operator*(real2x2 Lhs, real2x4 Rhs) {
		real2x4 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real2x2 operator*(real2x3 Lhs, real3x2 Rhs) {
		real2x2 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real2x3 operator*(real2x3 Lhs, real3x3 Rhs) {
		real2x3 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real2x4 operator*(real2x3 Lhs, real3x4 Rhs) {
		real2x4 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real2x2 operator*(real2x4 Lhs, real4x2 Rhs) {
		real2x2 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real2x3 operator*(real2x4 Lhs, real4x3 Rhs) {
		real2x3 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real2x4 operator*(real2x4 Lhs, real4x4 Rhs) {
		real2x4 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real3x2 operator*(real3x2 Lhs, real2x2 Rhs) {
		real3x2 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real3x3 operator*(real3x2 Lhs, real2x3 Rhs) {
		real3x3 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real3x4 operator*(real3x2 Lhs, real2x4 Rhs) {
		real3x4 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real3x2 operator*(real3x3 Lhs, real3x2 Rhs) {
		real3x2 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real3x4 operator*(real3x3 Lhs, real3x4 Rhs) {
		real3x4 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real3x2 operator*(real3x4 Lhs, real4x2 Rhs) {
		real3x2 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real3x3 operator*(real3x4 Lhs, real4x3 Rhs) {
		real3x3 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real3x4 operator*(real3x4 Lhs, real4x4 Rhs) {
		real3x4 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real4x2 operator*(real4x2 Lhs, real2x2 Rhs) {
		real4x2 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real4x3 operator*(real4x2 Lhs, real2x3 Rhs) {
		real4x3 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real4x4 operator*(real4x2 Lhs, real2x4 Rhs) {
		real4x4 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real4x2 operator*(real4x3 Lhs, real3x2 Rhs) {
		real4x2 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real4x3 operator*(real4x3 Lhs, real3x3 Rhs) {
		real4x3 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real4x4 operator*(real4x3 Lhs, real3x4 Rhs) {
		real4x4 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real4x2 operator*(real4x4 Lhs, real4x2 Rhs) {
		real4x2 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	real4x3 operator*(real4x4 Lhs, real4x3 Rhs) {
		real4x3 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

}