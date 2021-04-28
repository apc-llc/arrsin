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

