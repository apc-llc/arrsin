#include <algorithm>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <execution>
#include <random>
#include <vector>

#include "xsimd/xsimd.hpp"

using namespace std;

using vector_type = std::vector<double, xsimd::aligned_allocator<double, XSIMD_DEFAULT_ALIGNMENT>>;

int main(int argc, char* argv[])
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(-1, 1);

	vector_type x(1e8);
	generate(x.begin(), x.end(), [&dist, &gen]()
	{
		return dist(gen);
	});

	auto t1 = std::chrono::system_clock::now();
	xsimd::transform(/*std::execution::par_unseq,*/ x.begin(), x.end(), x.begin(),
		[&](const auto xi) { return xsimd::sin(xi); });
	auto t2 = std::chrono::system_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("%f\n", time / 1e6);

	return 0;
}

// ./arrsin
// 1.098075

