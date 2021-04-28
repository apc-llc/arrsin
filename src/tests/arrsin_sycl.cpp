#include <algorithm>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <random>
#include <vector>
#include <oneapi/dpl/execution>
#include <oneapi/dpl/algorithm>
#include <CL/sycl.hpp>
#include "check.h"

using namespace std;

using fptype = FPTYPE;

class prefer_gpu : public sycl::device_selector
{
public :
	int operator()(const sycl::device &dev) const override
	{
		if (dev.is_gpu()) return 1;
		if (dev.is_cpu()) return 2;
		return 0;
	}
};

int main(int argc, char* argv[])
{
	std::mt19937 gen;
	std::uniform_real_distribution<> dist(-1, 1);

	vector<fptype> x(1e8);
	generate(x.begin(), x.end(), [&dist, &gen]()
	{
		return dist(gen);
	});

	prefer_gpu selector;
	sycl::queue q(selector);
	std::cout << "Executing on " << q.get_device().get_info<sycl::info::device::name>() << std::endl;
	//std::cout << "preferred_vector_width_fptype = " << q.get_device().get_info<sycl::info::device::preferred_vector_width_fptype>() << std::endl;

	fptype* x_dev = sycl::malloc_device<fptype>(x.size(), q);

	std::copy(x.data(), x.data() + x.size(), x_dev);

	auto t1 = std::chrono::system_clock::now();
	std::transform(oneapi::dpl::execution::make_device_policy(q), x_dev, x_dev + x.size(), x_dev,
		[&](fptype xi) -> fptype { return cl::sycl::sin(xi); });
	q.wait();
	auto t2 = std::chrono::system_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("%f\n", time / 1e6);

	std::copy(x_dev, x_dev + x.size(), x.data());
	sycl::free(x_dev, q);

	check(x);

	return 0;
}

// BENCH DEV Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz
// BENCH NAME GPU Intel float (C++)
// BENCH EXEC ./arrsin_sycl_float
// BENCH SCORE 0.314744
// BENCH CHECK check sum = -3187.199946

// BENCH DEV Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz
// BENCH NAME GPU Intel double (C++)
// BENCH EXEC ./arrsin_sycl_double
// BENCH SCORE 0.435768
// BENCH CHECK check sum = -3187.199840

