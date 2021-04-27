#include <algorithm>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <execution>
#include <random>
#include <vector>
#include "check.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::mt19937 gen;
	std::uniform_real_distribution<> dist(-1, 1);

	vector<double> x(1e8);
	generate(x.begin(), x.end(), [&dist, &gen]()
	{
		return dist(gen);
	});

	auto t1 = std::chrono::system_clock::now();
	std::transform(std::execution::par_unseq, x.begin(), x.end(), x.begin(),
		[&](double xi) -> double { return sin(xi); });
	auto t2 = std::chrono::system_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("%f\n", time / 1e6);

	check(x);

	return 0;
}

// ./arrsin_par
// 0.290954
// check sum = -3187.199840

