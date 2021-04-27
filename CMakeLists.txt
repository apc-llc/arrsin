cmake_minimum_required(VERSION 3.8)

project(arrsin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

find_package(IntelDPCXX)

add_subdirectory(ThirdParty/xsimd)

add_subdirectory(src/tests)

