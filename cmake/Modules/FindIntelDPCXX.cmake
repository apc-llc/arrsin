find_program(CMAKE_DPCXX_COMPILER NAMES dpcpp)

if (CMAKE_DPCXX_COMPILER)
set(CMAKE_DPCXX_COMPILER_ENV_VAR ${CMAKE_DPCXX_COMPILER})
enable_language(DPCXX)
message(STATUS "Found dpcpp compiler")
else()
message(STATUS "Not compiling for Intel DPC++ backend, because dpcpp executable is not found in the $PATH (Intel® oneAPI Base Toolkit could be downloaded from https://software.intel.com/content/www/us/en/develop/tools/oneapi/base-toolkit/download.html")
endif()

# Special treatment for the specified source files of target that need to be handled
# by the Intel oneAPI DPC++ compiler
function(target_compile_sycl target)

if (CMAKE_DPCXX_COMPILER)
set(sources ${ARGN})
set(CMAKE_DPCXX_FLAGS "-stdpar")
foreach(source IN LISTS sources)
	set_source_files_properties(${source} PROPERTIES LANGUAGE DPCXX)
endforeach()
set_target_properties(${target} PROPERTIES LINKER_LANGUAGE DPCXX)
target_compile_definitions(${target} PRIVATE HAVE_DPCXX)
else()
message(STATUS "Not compiling for Intel DPC++ backend, because dpcpp executable is not found in the $PATH (Intel® oneAPI Base Toolkit could be downloaded from https://software.intel.com/content/www/us/en/develop/tools/oneapi/base-toolkit/download.html")
endif()

endfunction()

