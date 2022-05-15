#include <geodesuka/core/math/matrix/multiply.h>

//tex:
// Matrix Multiplication
// $$C = AB$$
// $$ c_{ij} = \sum_{k} a_{ik} b_{kj} $$

namespace geodesuka::core::math {

	float2x3 operator*(float2x2 Lhs, float2x3 Rhs) {
		float2x3 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float2x4 operator*(float2x2 Lhs, float2x4 Rhs) {
		float2x4 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float2x2 operator*(float2x3 Lhs, float3x2 Rhs) {
		float2x2 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float2x3 operator*(float2x3 Lhs, float3x3 Rhs) {
		float2x3 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float2x4 operator*(float2x3 Lhs, float3x4 Rhs) {
		float2x4 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float2x2 operator*(float2x4 Lhs, float4x2 Rhs) {
		float2x2 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float2x3 operator*(float2x4 Lhs, float4x3 Rhs) {
		float2x3 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float2x4 operator*(float2x4 Lhs, float4x4 Rhs) {
		float2x4 Temp;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float3x2 operator*(float3x2 Lhs, float2x2 Rhs) {
		float3x2 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float3x3 operator*(float3x2 Lhs, float2x3 Rhs) {
		float3x3 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float3x4 operator*(float3x2 Lhs, float2x4 Rhs) {
		float3x4 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float3x2 operator*(float3x3 Lhs, float3x2 Rhs) {
		float3x2 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float3x4 operator*(float3x3 Lhs, float3x4 Rhs) {
		float3x4 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float3x2 operator*(float3x4 Lhs, float4x2 Rhs) {
		float3x2 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float3x3 operator*(float3x4 Lhs, float4x3 Rhs) {
		float3x3 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float3x4 operator*(float3x4 Lhs, float4x4 Rhs) {
		float3x4 Temp;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float4x2 operator*(float4x2 Lhs, float2x2 Rhs) {
		float4x2 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float4x3 operator*(float4x2 Lhs, float2x3 Rhs) {
		float4x3 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float4x4 operator*(float4x2 Lhs, float2x4 Rhs) {
		float4x4 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 2; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float4x2 operator*(float4x3 Lhs, float3x2 Rhs) {
		float4x2 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float4x3 operator*(float4x3 Lhs, float3x3 Rhs) {
		float4x3 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 3; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float4x4 operator*(float4x3 Lhs, float3x4 Rhs) {
		float4x4 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 3; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float4x2 operator*(float4x4 Lhs, float4x2 Rhs) {
		float4x2 Temp;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 2; j++) {
				for (int k = 1; k <= 4; k++) {
					Temp(i, j) += Lhs(i, k) * Rhs(k, j);
				}
			}
		}
		return Temp;
	}

	float4x3 operator*(float4x4 Lhs, float4x3 Rhs) {
		float4x3 Temp;
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