/*
 * Ultraword.cpp
 *
 *  Created on: Aug 17, 2023
 *      Author: max
 */


#include "Ultraword32.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <sstream>

Ultraword32 Ultraword32::Zero() {
	Ultraword32 Uw;
	Uw.upper = _mm512_setzero_si512();
	Uw.lower = _mm512_setzero_si512();
	return Uw;
}

Ultraword32 Ultraword32::Copy(uint32_t value) {
	Ultraword32 Uw;
	Uw.upper = _mm512_set1_epi32(value);
	Uw.lower = _mm512_set1_epi32(value);
	return Uw;
}

void Ultraword32::add_componentwise(Ultraword32 other) {
	upper = _mm512_add_epi32(upper, other.upper);
	lower = _mm512_add_epi32(lower, other.lower);
}

void Ultraword32::left_shift_componentwise(Ultraword32 other, int by) {
	upper = _mm512_sll_epi32(upper, by);
	lower = _mm512_sll_epi32(lower, by);
}

int main() {
	std::string test = "ABC DEF GHI   ";
	std::istringstream iss (test);
	std::string first, second, third;
	iss >> first;
	iss >> second;
	iss >> third;
	std::cout << "Got: \"" << first << second << third << "\"" << std::endl;
}

void test_times() {
	Ultraword32 Uw(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
	Uw.setUpper(31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16);

	int v1 = Uw.OldGet(13);
	int v2 = Uw.OldGet(20);
	int v3 = Uw.OldGet(0);
	int v4 = Uw.OldGet(31);
	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;
	std::cout << v4 << std::endl;

	//Efficiency test
	//random index generator
	const int range_from = 0;
	const int range_to = 32;
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> distr(range_from, range_to);

	//time
	int reps = 10;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < reps; i++) {
		volatile int x = Uw.OldGet(distr(generator));
		//std::cout << x;
	}
	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << std::endl;
	std::cout << "TIME FOR " << reps << " REPETITIONS OF NORMAL GET: " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << std::endl;

	//time
	auto start2 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < reps; i++) {
		volatile int x = Uw.get(distr(generator));
		//std::cout << x;
	}
	auto finish2 = std::chrono::high_resolution_clock::now();
	std::cout << std::endl;
	std::cout << "TIME FOR " << reps << " REPETITIONS OF GET 2: " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish2-start2).count() << std::endl;
}

