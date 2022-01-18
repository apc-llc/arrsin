#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <execution>
#include <random>
#include <vector>
#include "check.h"

#define CUDA_ERR_CHECK(x) \
        do { cudaError_t err = x; if (err != cudaSuccess) { \
                fprintf (stderr, "Error \"%s\" at %s:%d \n", \
                 cudaGetErrorString(err), \
                __FILE__, __LINE__); exit(-1); \
        }} while (0);

using namespace std;

using fptype = FPTYPE;

__global__ void kernel(fptype* x)
{
	int i = threadIdx.x + blockDim.x * blockIdx.x;
	x[i] = sin(x[i]);
}

int main(int argc, char* argv[])
{
	std::mt19937 gen;
	std::uniform_real_distribution<> dist(-1, 1);

	vector<fptype> x(1e8);
	generate(x.begin(), x.end(), [&dist, &gen]()
	{
		return dist(gen);
	});

	int szblock = 128;
	fptype* x_dev = nullptr;
	size_t nblocks = x.size() / szblock;
	nblocks += x.size() % szblock ? 1 : 0;
	CUDA_ERR_CHECK(cudaMalloc(&x_dev, szblock * nblocks * sizeof(fptype)));
	CUDA_ERR_CHECK(cudaMemcpy(x_dev, x.data(), x.size() * sizeof(fptype), cudaMemcpyHostToDevice));

	auto t1 = std::chrono::high_resolution_clock::now();

	kernel<<<nblocks, szblock>>>(x_dev);
	CUDA_ERR_CHECK(cudaGetLastError());
	CUDA_ERR_CHECK(cudaDeviceSynchronize());

	auto t2 = std::chrono::high_resolution_clock::now();
	
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("%f\n", time / 1e6);
	
	CUDA_ERR_CHECK(cudaMemcpy(x.data(), x_dev, x.size() * sizeof(fptype), cudaMemcpyDeviceToHost));
	CUDA_ERR_CHECK(cudaFree(x_dev));

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

