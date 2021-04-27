cmake_minimum_required(VERSION 3.8)

project(arrsin_tests)

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

if (CMAKE_DPCXX_COMPILER)
add_executable(arrsin_sycl arrsin_sycl.cpp)
target_compile_sycl(arrsin_sycl arrsin_sycl.cpp)
endif()

