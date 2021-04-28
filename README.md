Name | Time | Check | Executable
--- | --- | --- | ---
CPU (Python) | 1.529520 | check sum = -3187.199840 | python3 ./arrsin.py
CPU 1-core (C++) | 0.552441 | check sum = -3187.199840 | ./arrsin
CPU 4-core (C++) | 0.290954 | check sum = -3187.199840 | ./arrsin_par
CPU 1-core SIMD (C++) | 0.376184 | check sum = -3187.199840 | ./arrsin_xsimd
CPU 4-core SIMD (C++) | 0.104423 | check sum = -3187.199840 | ./arrsin_par_xsimd
GPU Intel float (C++) | 0.314744 | check sum = -3187.199946 | ./arrsin_sycl_float
GPU Intel double (C++) | 0.435768 | check sum = -3187.199840 | ./arrsin_sycl_double
GPU GTX1060M float (nvc++ -stdpar) | 0.005465 | check sum = -3187.200205 | ./arrsin_nvpar_float
GPU GTX1060M double (nvc++ -stdpar) | 0.030684 | check sum = -3187.199840 | ./arrsin_nvpar_double
GPU V100 float (nvc++ -stdpar) | 0.001142 | check sum = -3187.200205 | ./arrsin_nvpar_float
GPU V100 double (nvc++ -stdpar) | 0.002970 | check sum = -3187.199840 | ./arrsin_nvpar_double
GPU A100 float (nvc++ -stdpar) | 0.001030 | check sum = -3187.200205 | ./arrsin_nvpar_float
GPU A100 double (nvc++ -stdpar) | 0.005156 | check sum = -3187.199840 | ./arrsin_nvpar_double

## Prerequisites

In order to build std::parallel examples for CPU, a modern C++17 compiler is required, such as `g++ 9.3.0`.

[Download](https://developer.nvidia.com/hpc-sdk) and enable NVIDIA HPC SDK:

```
export PATH=$PATH:/opt/nvidia/hpc_sdk/Linux_x86_64/2021/compilers/bin
```

[Download](https://software.intel.com/content/www/us/en/develop/tools/oneapi/base-toolkit/download.html) and enable Intel oneAPI (compiler only, without TBB, which may clash with gcc's TBB):

```
source /opt/intel/oneapi/compiler/latest/env/vars.sh intel64
```

## Building

```
mkdir build
cd build
cmake ..
make -j4
```

## Testing

Binaries for all supported targets will be available in `build/src/test`.

