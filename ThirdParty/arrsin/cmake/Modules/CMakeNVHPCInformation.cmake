# This file defines a NVHPC language to be used for compiling
# a subset of project with Intel DPC++ compiler.

include(CMakeLanguageInformation)

if(UNIX)
set(CMAKE_NVHPC_OUTPUT_EXTENSION .o)
else()
set(CMAKE_NVHPC_OUTPUT_EXTENSION .obj)
endif()

find_program(CMAKE_NVHPC_COMPILER NAMES nvc++)

set(CMAKE_NVHPC_FLAGS_DEBUG "-g -O0")
set(CMAKE_NVHPC_FLAGS_RELEASE "-O3")
set(CMAKE_INCLUDE_FLAG_NVHPC "-I")
set(CMAKE_NVHPC_SOURCE_FILE_EXTENSIONS nvhpc)
set(CMAKE_SHARED_LIBRARY_RUNTIME_NVHPC_FLAG ${CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG})
set(CMAKE_SHARED_LIBRARY_RUNTIME_NVHPC_FLAG_SEP ${CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG_SEP})
set(CMAKE_SHARED_LIBRARY_RPATH_LINK_NVHPC_FLAG ${CMAKE_SHARED_LIBRARY_RPATH_LINK_C_FLAG})

# add the flags to the cache based
# on the initial values computed in the platform/*.cmake files
# use _INIT variables so that this only happens the first time
# and you can set these flags in the cmake cache
set(CMAKE_NVHPC_FLAGS_INIT "$ENV{CXXFLAGS} ${CMAKE_NVHPC_FLAGS_INIT}")

cmake_initialize_per_config_variable(CMAKE_NVHPC_FLAGS "Flags used by the NVC++ compiler")

include(CMakeCommonLanguageInclude)

set(CMAKE_NVHPC_CREATE_SHARED_LIBRARY "<CMAKE_NVHPC_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
set(CMAKE_NVHPC_CREATE_SHARED_MODULE ${CMAKE_DPCCXX_CREATE_SHARED_LIBRARY})
set(CMAKE_NVHPC_COMPILE_OBJECT "<CMAKE_NVHPC_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
set(CMAKE_NVHPC_LINK_EXECUTABLE "<CMAKE_NVHPC_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

mark_as_advanced(
CMAKE_VERBOSE_MAKEFILE
)

set(CMAKE_NVHPC_INFORMATION_LOADED 1)
