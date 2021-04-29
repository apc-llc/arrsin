#include <algorithm>
#include <cstdio>
#include <chrono>
#include <cmath>
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
	std::transform(x.begin(), x.end(), x.begin(),
		[&](double xi) -> double { return sin(xi); });
	auto t2 = std::chrono::system_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("%f\n", time / 1e6);

	check(x);

	return 0;
}

// BENCH DEV Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz
// BENCH NAME CPU 1-core (C++)
// BENCH EXEC ./arrsin
// BENCH SCORE 0.552441
// BENCH CHECK check sum = -3187.199840

