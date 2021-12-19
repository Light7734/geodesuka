#include <geodesuka/core/math/util/isupport.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <geodesuka/core/math/config.h>

// Levi Civita uses heap sort to determine sign by swap count.

static int sift_down(int* A, int Length, int i) {
	if ((i < 0) && (i >= Length)) return 0;
	static int SwapCount = 0;
	static int StackDepth = 0;
	StackDepth += 1;

	int L = 2 * i + 1; // Left Child
	int R = 2 * i + 2; // Right Child

	int SwapContainer;
	if ((L < Length) && (R < Length)) {
		if (A[L] > A[R]) {
			if (A[L] > A[i]) {
				SwapContainer = A[L];
				A[L] = A[i];
				A[i] = SwapContainer;
				SwapCount += 1;
				sift_down(A, Length, L);
			}
		}
		else {
			if (A[R] > A[i]) {
				SwapContainer = A[R];
				A[R] = A[i];
				A[i] = SwapContainer;
				SwapCount += 1;
				sift_down(A, Length, R);
			}
		}
	}
	else if (L < Length) {
		if (A[L] > A[i]) {
			SwapContainer = A[L];
			A[L] = A[i];
			A[i] = SwapContainer;
			SwapCount += 1;
		}
	}

	StackDepth -= 1;
	if (StackDepth == 0) {
		int SwapTotal = SwapCount;
		SwapCount = 0;
		return SwapTotal;
	}
	else {
		return 0;
	}
}

static int build_heap(int* A, int Length) {
	int SwapCount = 0;
	for (int i = Length - 1; i >= 0; i--) {
		if (2 * i + 1 >= Length) continue;
		SwapCount += sift_down(A, Length, i);
	}
	return SwapCount;
}

static int heap_sort(int* A, int Length) {
	int SwapCount = 0;
	SwapCount += build_heap(A, Length);
	int SwapContainer;
	int HeapSize = Length;
	while (HeapSize > 1) {
		SwapContainer = A[0];
		A[0] = A[HeapSize - 1];
		A[HeapSize - 1] = SwapContainer;
		HeapSize -= 1;
		SwapCount += 1;
		SwapCount += sift_down(A, HeapSize, 0);
	}
	return SwapCount;
}

// Probably Delete
int kronecker_delta(int I, int J) {
	return (I == J) ? 1 : 0;
}

//tex:
// The Levi Civita Symbol is known for its skew-symmetric nature.
// The property being that if any two of the indices are swapped,
// it is the negative of itself. If any two indices repeat, just
// swapping those two particular indices lead to the same entry,
// therefore leaving only zero to be the possible answer. The rank
// of the tensor is then $n$, with $n$ indices. The larger the matrix
// gets, the less feasible this is to calculate. There must be other
// methods.
// $$ i_{1}, i_{2}, i_{3}, ... i_{n} \in [1, n] $$
// $$ \varepsilon_{i_{1}, i_{2}, ... i_{n}} \in \{ -1, 0, +1 \} $$
int levi_civita(int aRank, const int* aIndex) {
	//tex:
	// All values must be $ i_{1}, i_{2}, i_{3},...i_{n} \in [1, n] $
	// $$ \varepsilon_{i_{i} i_{2} ... i_{n}} \in \{ -1, 0, +1 \}$$
	// If any indices repeat, then $\varepsilon_{i_{i} i_{2} ... i_{n}} = 0$
	if ((aRank <= 0) || (aIndex == NULL)) return 0;
	//tex:
	// Checks for index values in $ i_{j} \in [1, n] $.
	for (int i = 0; i < aRank; i++) {
		if ((aIndex[i] < 1) || (aIndex[i] >= aRank)) return 0;
	}
	//tex:
	// Checks for duplicate indices, returns 0 if there are duplicates.
	for (int i = 0; i < aRank; i++) {
		for (int j = i + 1; j < aRank; j++) {
			if (aIndex[i] == aIndex[j]) return 0;
		}
	}
	// Indices are valid, and unique. Sort to find signature.
	int* Index = (int*)malloc(aRank * sizeof(int));
	if (Index == NULL) return 0;
	memcpy(Index, aIndex, aRank * sizeof(int));
	int IndexSwapCount = heap_sort(Index, aRank);
	free(Index);
	return (((IndexSwapCount % 2) > 0) ? -1 : +1);
}

// This is the same function, but for syntactical sugar.
int levi_civita(int aRank, ...) {

	//int i = 0;
	//int j = 0;

	int* Index = NULL;
	Index = (int*)malloc(aRank * sizeof(int));
	if (Index == NULL) return 0;

	va_list ArgList;
	va_start(ArgList, aRank);
	for (int i = 0; i < aRank; i++) {
		// Assumes user is not retarded.
		Index[i] = va_arg(ArgList, int);
	}
	va_end(ArgList);

	//// Checks for illegal values.
	//for (i = 0; i < aRank; i++) {
	//	if ((Index[i] < 0) && (Index[i] >= aRank)) {
	//		free(Index); Index = NULL;
	//		return 0;
	//	}
	//}

	//// Checks for duplicate values.
	//for (i = 0; i < aRank; i++) {
	//	for (j = i + 1; j < aRank; j++) {
	//		if (Index[i] == Index[j]) {
	//			free(Index); Index = NULL;
	//			return 0;
	//		}
	//	}
	//}

	int temp = levi_civita(aRank, Index);

	free(Index); Index = NULL;

	return temp;
}

/*
int levi_civita(int Rank, ...) {
#ifdef LEVI_CEVITA_STACK_MEMORY
		if (Rank > LEVI_CEVITA_STACK_MEMORY_SIZE) return 0;
#endif // LEVI_CEVITA_STACK_MEMORY


		int i = 0;
		int j = 0;

#ifdef LEVI_CEVITA_STACK_MEMORY
		int Index[LEVI_CEVITA_STACK_MEMORY_SIZE];
#else
		int* Index = NULL;
		Index = (int*)malloc(Rank * sizeof(int));
		if (Index == NULL) return 0;
#endif // LEVI_CEVITA_STACK_MEMORY

		va_list ArgList;
		va_start(ArgList, Rank);
		for (int i = 0; i < Rank; i++) {
			Index[i] = va_arg(ArgList, int);
		}
		va_end(ArgList);

		for (i = 0; i < Rank; i++) {
			if ((Index[i] < 0) && (Index[i] >= Rank)) {
#ifndef LEVI_CEVITA_STACK_MEMORY
				free(Index); Index = NULL;
#endif // !LEVI_CEVITA_STACK_MEMORY
				return 0;
			}
		}

		for (i = 0; i < Rank; i++) {
			for (j = i + 1; j < Rank; j++) {
				if (Index[i] == Index[j]) {
#ifndef LEVI_CEVITA_STACK_MEMORY
					free(Index); Index = NULL;
#endif // !LEVI_CEVITA_STACK_MEMORY
					return 0;
				}
			}
		}

		int IndexSwapCount = heap_sort(Index, Rank);

#ifndef LEVI_CEVITA_STACK_MEMORY
		free(Index); Index = NULL;
#endif // !LEVI_CEVITA_STACK_MEMORY

		if ((IndexSwapCount % 2) > 0) {
			return -1;
		}
		else {
			return +1;
		}
	}
	//*/



