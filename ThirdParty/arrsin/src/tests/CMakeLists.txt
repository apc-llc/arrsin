cmake_minimum_required(VERSION 3.18)

project(arrsin_tests)

enable_language(CUDA)

add_executable(arrsin arrsin.cpp)
set_property(TARGET arrsin PROPERTY CXX_STANDARD 17)
target_compile_options(arrsin PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-g -O3 -ffast-math>)

add_executable(arrsin_par arrsin_par.cpp)
set_property(TARGET arrsin_par PROPERTY CXX_STANDARD 17)
target_compile_options(arrsin_par PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-g -O3 -ffast-math>)
target_link_libraries(arrsin_par PRIVATE tbb)

add_executable(arrsin_xsimd arrsin_xsimd.cpp)
set_property(TARGET arrsin_xsimd PROPERTY CXX_STANDARD 17)
target_compile_options(arrsin_xsimd PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-g -O3 -ffast-math -mavx>)
target_link_libraries(arrsin_xsimd PRIVATE tbb xsimd)

add_executable(arrsin_par_xsimd arrsin_par_xsimd.cpp)
set_property(TARGET arrsin_par_xsimd PROPERTY CXX_STANDARD 17)
target_compile_options(arrsin_par_xsimd PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-g -O3 -ffast-math -mavx>)
target_link_libraries(arrsin_par_xsimd PRIVATE tbb xsimd)

add_executable(arrsin_cuda_float arrsin.cu)
set_property(TARGET arrsin_cuda_float PROPERTY CUDA_ARCHITECTURES 60 80)
target_compile_definitions(arrsin_cuda_float PRIVATE FPTYPE=float)

add_executable(arrsin_cuda_double arrsin.cu)
set_property(TARGET arrsin_cuda_double PROPERTY CUDA_ARCHITECTURES 60 80)
target_compile_definitions(arrsin_cuda_double PRIVATE FPTYPE=double)

if (CMAKE_DPCXX_COMPILER)
add_executable(arrsin_sycl_float arrsin_sycl.cpp)
target_compile_sycl(arrsin_sycl_float arrsin_sycl.cpp)
target_compile_definitions(arrsin_sycl_float PRIVATE FPTYPE=float)

add_executable(arrsin_sycl_double arrsin_sycl.cpp)
target_compile_sycl(arrsin_sycl_double arrsin_sycl.cpp)
target_compile_definitions(arrsin_sycl_double PRIVATE FPTYPE=double)
endif()

if (CMAKE_NVHPC_COMPILER)
add_executable(arrsin_nvpar_float arrsin_nvpar.cpp)
set(GPU_ARCH 80) # Volta
target_compile_nvpar(arrsin_nvpar_float ${GPU_ARCH} arrsin_nvpar.cpp)
target_compile_definitions(arrsin_nvpar_float PRIVATE FPTYPE=float)

add_executable(arrsin_nvpar_double arrsin_nvpar.cpp)
set(GPU_ARCH 60) # Pascal
target_compile_nvpar(arrsin_nvpar_double ${GPU_ARCH} arrsin_nvpar.cpp)
target_compile_definitions(arrsin_nvpar_double PRIVATE FPTYPE=double)

add_executable(arrsin_openacc_float arrsin_openacc.cpp)
set(GPU_ARCH 80) # Volta
target_compile_openacc(arrsin_openacc_float ${GPU_ARCH} arrsin_openacc.cpp)
target_compile_definitions(arrsin_openacc_float PRIVATE FPTYPE=float)

add_executable(arrsin_openacc_double arrsin_openacc.cpp)
set(GPU_ARCH 60) # Pascal
target_compile_openacc(arrsin_openacc_double ${GPU_ARCH} arrsin_openacc.cpp)
target_compile_definitions(arrsin_openacc_double PRIVATE FPTYPE=double)
endif()

