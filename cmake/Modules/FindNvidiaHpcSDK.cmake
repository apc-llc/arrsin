find_program(CMAKE_NVHPC_COMPILER NAMES nvc++)

if (CMAKE_NVHPC_COMPILER)
set(CMAKE_NVHPC_COMPILER_ENV_VAR ${CMAKE_NVHPC_COMPILER})
enable_language(NVHPC)
message(STATUS "Found nvc++ compiler")
else()
message(STATUS "Not compiling the NVIDIA GPU backend, because nvc++ executable is not found in the $PATH (NVIDIA HPC SDK could be downloaded from https://developer.nvidia.com/hpc-sdk)")
endif()

# Special treatment for the specified source files of target that need to be handled
# by the Intel oneAPI DPC++ compiler
function(target_compile_nvpar target gpu_arch)

if (CMAKE_NVHPC_COMPILER)
set(sources ${ARGN})
foreach(source IN LISTS sources)
	set_source_files_properties(${source} PROPERTIES
		LANGUAGE NVHPC
		COMPILE_FLAGS "-stdpar -std=c++17 -gpu=cc${gpu_arch}")
endforeach()
set_target_properties(${target} PROPERTIES
	LINKER_LANGUAGE NVHPC
	LINK_OPTIONS "-stdpar")
target_compile_definitions(${target} PRIVATE HAVE_NVHPC)
else()
message(STATUS "Not compiling the NVIDIA GPU backend, because nvc++ executable is not found in the $PATH (NVIDIA HPC SDK could be downloaded from https://developer.nvidia.com/hpc-sdk)")
endif()

endfunction()

