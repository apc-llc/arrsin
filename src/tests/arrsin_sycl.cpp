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

	vector<double> x(1e8);
	generate(x.begin(), x.end(), [&dist, &gen]()
	{
		return dist(gen);
	});

	prefer_gpu selector;
	sycl::queue q(selector);
	std::cout << "Executing on " << q.get_device().get_info<sycl::info::device::name>() << std::endl;
	std::cout << "preferred_vector_width_double = " << q.get_device().get_info<sycl::info::device::preferred_vector_width_double>() << std::endl;

	double* x_dev = sycl::malloc_device<double>(x.size(), q);

	std::copy(x.data(), x.data() + x.size(), x_dev);

	auto t1 = std::chrono::system_clock::now();
	std::transform(oneapi::dpl::execution::make_device_policy(q), x_dev, x_dev + x.size(), x_dev,
		[&](double xi) -> double { return cl::sycl::sin(xi); });
	q.wait();
	auto t2 = std::chrono::system_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	printf("%f\n", time / 1e6);

	std::copy(x_dev, x_dev + x.size(), x.data());
	sycl::free(x_dev, q);

	check(x);

	return 0;
}

// ./arrsin_sycl

