/*
 * CppTests.cpp
 *
 *  Created on: Sep 7, 2023
 *      Author: max
 */


#include "Ultraword32.hpp"

bool verify_add_componentwise(Ultraword32 A, Ultraword32 B) {
	uint32_t sums[32];
	for (int i = 0; i < 32; i++) {
		sums[i] = A.get(i) + B.get(i);
	}
	A.add_componentwise(B);
	int i = 0;
	while (i < 32 && A.get(i) == sums[i]) {
		i++;
	}
	return i==32;
}
