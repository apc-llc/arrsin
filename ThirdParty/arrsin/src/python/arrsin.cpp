#include <algorithm>
#include <cstdio>
#include <chrono>
#include <cmath>
#include <execution>
#include <random>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

using namespace std;

void arrsin_par(std::vector<double>& x)
{
	std::transform(std::execution::par_unseq, x.begin(), x.end(), x.begin(),
                [&](double xi) -> double { return sin(xi); });
}

PYBIND11_MODULE(arrsin, m)
{
	// Define a function, which should be exported to Python
	m.def("arrsin_par", &arrsin_par, "Call a C++ Parallel STL Implementation of arrrsin");
}

