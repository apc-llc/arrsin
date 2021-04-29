cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

project(example)

if ("x" STREQUAL "x${CMAKE_BUILD_TYPE}")
set(CMAKE_BUILD_TYPE Release)
endif()

if (UNIX)
# Use $ORIGIN or @loader_path, which allow to pick up
# dependencies relative to the executable folder
if (APPLE)
set(CMAKE_INSTALL_RPATH "@loader_path" "@loader_path/.." "@loader_path/lib" "@loader_path/../lib")
else()
set(CMAKE_INSTALL_RPATH "$ORIGIN" "$ORIGIN/.." "$ORIGIN/lib" "$ORIGIN/../lib")
endif()
endif()

set(CUDA_USE_STATIC_CUDA_RUNTIME OFF CACHE INTERNAL "")

# Search path for CMake include files.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/gpurt/cmake)

# Enable C++ 14 support
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

if ("x${Python3_VERSION}" STREQUAL "x")
find_package(Python3 COMPONENTS Interpreter Development)
else()
find_package(Python3 ${Python3_VERSION} EXACT COMPONENTS Interpreter Development)
endif()
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})
message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")

set(PYBIND11_PYTHON_VERSION ${Python3_VERSION})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/pybind11)

file(GLOB SRC "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SRC} ${OpenCV_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/example.h")

pybind11_add_module(${PROJECT_NAME}_python "src/python/${PROJECT_NAME}.cpp" "src/python/${PROJECT_NAME}_module.cpp")
target_include_directories(${PROJECT_NAME}_python PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(${PROJECT_NAME}_python PRIVATE ${PROJECT_NAME}_EXPORTS)
target_link_libraries(${PROJECT_NAME}_python PRIVATE ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_python PROPERTIES LIBRARY_OUTPUT_NAME "${PROJECT_NAME}")

add_executable(${PROJECT_NAME}_console "src/console/${PROJECT_NAME}.cpp")
target_include_directories(${PROJECT_NAME}_console PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(${PROJECT_NAME} PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set_target_properties(${PROJECT_NAME}_python PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set_target_properties(${PROJECT_NAME}_console PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION . PUBLIC_HEADER DESTINATION include)
install(TARGETS ${PROJECT_NAME}_python DESTINATION .)
install(TARGETS ${PROJECT_NAME}_console DESTINATION .)

string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} ARCH)
string(TOLOWER ${CMAKE_SYSTEM_NAME} OS)
set(ARCHIVE "${PROJECT_NAME}-${ARCH}-${OS}-${BUILD_TYPE}")
set(CPACK_PACKAGE_FILE_NAME ${ARCHIVE})
set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_INSTALL_PREFIX})

include(CPack)
