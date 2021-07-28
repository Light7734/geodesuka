#pragma once
#ifndef GCLM_BASIC_UTIL_H
#define GCLM_BASIC_UTIL_H

#include <stdarg.h>

#include "../config.h"

/*
* This is supposed to be a backend library for the other classes.
* levi_cevita is used to find determinants of NxN matrices.
* can be extended to any size matrix to compute determinant.
*/

namespace geodesuka {
	namespace core {
		namespace math {

			//int sift_down(int* A, int Length, int i);
			//int build_heap(int* A, int Length);
			//int heap_sort(int* A, int Length);

			int kronecker_delta(int I, int J);
			int levi_civita(int aRank, const int* aIndex);
			int levi_civita(int aRank, ...);

		}
	}
}

#endif // !GCLM_BASIC_UTIL_H
