#include <algorithm>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <execution>
#include <random>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include "check.h"

namespace py = pybind11;

using namespace std;

static void arrsin(std::vector<double>& x)
{
        constexpr std::size_t simd_size = xsimd::simd_type<double>::size;
        std::size_t simd_length = x.size() / simd_size;

	std::transform(std::execution::par_unseq, x.begin(), x.end(), x.begin(),
                [&](double xi) -> double { return sin(xi); });
}

PYBIND11_MODULE(arrsin, arrsin)
{
	// Define a function, which should be exported to Python
	arrsin.def("arrsin", &arrsin, "Call a C++ Parallel STL Implementation of arrrsin");
}

