/*
 * Ultraword32.hpp
 *
 *  Created on: Aug 17, 2023
 *      Author: max
 */

#ifndef ULTRAWORD32_HPP_
#define ULTRAWORD32_HPP_

#include <immintrin.h>
#include <cstdint>
#include <iostream>

class Ultraword32 {

private:
	__m512i upper {}; //value initialization
	__m512i lower {};

public:
	Ultraword32() {
		upper = _mm512_undefined_epi32();
		lower = _mm512_undefined_epi32();
	}

	Ultraword32(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6,
			uint32_t a7, uint32_t a8, uint32_t a9, uint32_t a10, uint32_t a11, uint32_t a12, uint32_t a13,
			uint32_t a14, uint32_t a15) {
		lower = _mm512_set_epi32(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
	}

	void setUpper(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6,
			uint32_t a7, uint32_t a8, uint32_t a9, uint32_t a10, uint32_t a11, uint32_t a12, uint32_t a13,
			uint32_t a14, uint32_t a15) {
		upper = _mm512_set_epi32(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
	}

	static Ultraword32 Zero();

	static Ultraword32 Copy(uint32_t value);

	static void print_512_int_vector(__m512i vector) {
		int *i = (int *) &vector;
		std::cout << "HAAA" << std::endl;
		for (int ix = 15; ix > 0; ix--) {
			std::cout << i[ix] << ", ";
		}
		std::cout << i[0] << std::endl;
	}

	void add_componentwise(Ultraword32 other);

	void left_shift_componentwise(Ultraword32 other, int by);

	uint32_t get(int idx) {
		int *p;
		if (idx < 16) {
			p = (int *) &lower;
			return p[idx];
		} else {
			p = (int *) &upper;
			return p[idx - 16];
		}
	}

	uint32_t OldGet(int idx) {
    	if (idx < 16) {
    		__m512i shuf = _mm512_castsi128_si512( _mm_cvtsi32_si128(idx));
        	__m512i res = _mm512_permutexvar_epi32(shuf, lower);
        	return _mm_cvtsi128_si32(_mm512_castsi512_si128 (res));
    	} else {
    		__m512i shuf = _mm512_castsi128_si512( _mm_cvtsi32_si128(idx - 16));
    		__m512i res = _mm512_permutexvar_epi32(shuf, upper);
    		return _mm_cvtsi128_si32(_mm512_castsi512_si128 (res));
    	}
	}

	void lol(__m512i vec) {
		int a = _mm512_reduce_min_epi32(vec);
	}
};



#endif /* ULTRAWORD32_HPP_ */
