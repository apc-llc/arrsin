#include <algorithm>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <execution>
#include <random>
#include <vector>
#include "check.h"

#include "xsimd/xsimd.hpp"

using namespace std;

using vector_type = std::vector<double, xsimd::aligned_allocator<double, XSIMD_DEFAULT_ALIGNMENT>>;

int main(int argc, char* argv[])
{
	std::mt19937 gen;
	std::uniform_real_distribution<> dist(-1, 1);

	vector_type x(1e8);
	generate(x.begin(), x.end(), [&dist, &gen]()
	{
		return dist(gen);
	});

	constexpr std::size_t simd_size = xsimd::simd_type<double>::size;
	std::size_t simd_length = x.size() / simd_size;

	auto t1 = std::chrono::system_clock::now();
	auto data = reinterpret_cast<xsimd::simd_type<double>::batch_type*>(x.data());
	std::transform(std::execution::par_unseq, data, data + simd_length, data,
		[&](const auto& xi) { return xsimd::sin(xi); });
	auto t2 = std::chrono::system_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("%f\n", time / 1e6);

	check(x);

	return 0;
}

// BENCH DEV Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz
// BENCH NAME CPU 4-core SIMD (C++)
// BENCH EXEC ./arrsin_par_xsimd
// BENCH SCORE 0.104423
// BENCH CHECK check sum = -3187.199840

