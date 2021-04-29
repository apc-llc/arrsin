cmake_minimum_required(VERSION 2.8)

project(arrsin-package)

set(CPACK_PACKAGE_NAME "example")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/arrsin)

