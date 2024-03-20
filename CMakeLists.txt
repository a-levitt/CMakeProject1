cmake_minimum_required (VERSION 3.26)

# Project name
project ("D3DFirst")

# Setting CMake options
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
endif()

# Setting C++ standard
set(CMAKE_CXX_STANDARD 20)

# Compiler version check
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message(STATUS "Using MSVC, ver. ${MSVC_VERSION}")
else()
	message(FATAL_ERROR "Compiler is not supported")
endif()

# Setting output directory
add_subdirectory ("Source")