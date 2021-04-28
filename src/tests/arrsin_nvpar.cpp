#include <algorithm>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <execution>
#include <random>
#include <vector>
#include <thrust/device_vector.h>
#include "check.h"

using namespace std;

using fptype = FPTYPE;

int main(int argc, char* argv[])
{
	std::mt19937 gen;
	std::uniform_real_distribution<> dist(-1, 1);

	vector<fptype> x(1e8);
	generate(x.begin(), x.end(), [&dist, &gen]()
	{
		return dist(gen);
	});

	thrust::device_vector<fptype> x_dev;
	x_dev.resize(x.size());

	thrust::copy(x.begin(), x.end(), x_dev.begin());

	auto t1 = std::chrono::system_clock::now();
	std::transform(std::execution::par_unseq, x_dev.begin(), x_dev.end(), x_dev.begin(),
		[&](fptype xi) -> fptype { return sin(xi); });
	auto t2 = std::chrono::system_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("%f\n", time / 1e6);

	thrust::copy(x_dev.begin(), x_dev.end(), x.begin());

	check(x);

	return 0;
}

// GTX 1060M
// ./arrsin_nvpar_double 
// 0.030684
// check sum = -3187.199840
// ./arrsin_nvpar_float
// 0.005465
// check sum = -3187.200205

// Tesla V100-SXM2-16GB
// ./arrsin_nvpar_double
// 0.002970
// check sum = -3187.199840
// ./arrsin_nvpar_float
// 0.001142
// check sum = -3187.200205

