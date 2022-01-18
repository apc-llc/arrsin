#include <algorithm>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <execution>
#include <random>
#include <vector>
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

	auto x_data = x.data();
	auto x_size = x.size();

	#pragma acc data copy(x_data[:x_size])
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		#pragma acc kernels
		for (int i = 0; i < x_size; i++)
			x_data[i] = sin(x_data[i]);
		auto t2 = std::chrono::high_resolution_clock::now();
	
		auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		printf("%f\n", time / 1e6);
	}

	check(x);

	return 0;
}

// BENCH DEV NVIDIA GeForce 1060M
// BENCH NAME GPU NVIDIA GTX1060M (nvc++ -stdpar)
// BENCH EXEC ./arrsin_nvpar_float
// BENCH SCORE 0.005465
// BENCH CHECK check sum = -3187.200205

// BENCH DEV NVIDIA GeForce 1060M
// BENCH NAME GPU NVIDIA GTX1060M (nvc++ -stdpar)
// BENCH EXEC ./arrsin_nvpar_double
// BENCH SCORE 0.030684
// BENCH CHECK check sum = -3187.199840

// BENCH DEV NVIDIA Tesla V100-SXM2-16GB
// BENCH NAME GPU NVIDIA V100 (nvc++ -stdpar)
// BENCH EXEC ./arrsin_nvpar_float
// BENCH SCORE 0.001142
// BENCH CHECK check sum = -3187.200205

// BENCH DEV NVIDIA Tesla V100-SXM2-16GB
// BENCH NAME GPU NVIDIA V100 (nvc++ -stdpar)
// BENCH EXEC ./arrsin_nvpar_double
// BENCH SCORE 0.002970
// BENCH CHECK check sum = -3187.199840

// BENCH DEV NVIDIA Tesla A100-SXM4-40GB
// BENCH NAME GPU NVIDIA A100 (nvc++ -stdpar)
// BENCH EXEC ./arrsin_nvpar_float
// BENCH SCORE 0.001030
// BENCH CHECK check sum = -3187.200205

// BENCH DEV NVIDIA Tesla A100-SXM4-40GB
// BENCH NAME GPU NVIDIA A100 (nvc++ -stdpar)
// BENCH EXEC ./arrsin_nvpar_double
// BENCH SCORE 0.005156
// BENCH CHECK check sum = -3187.199840

