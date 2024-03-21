cmake_minimum_required (VERSION 3.26)

# Include 3rd-party libraries
include("${CMAKE_SOURCE_DIR}/Scripts/FetchLibraries.cmake")

# Populate 3rd-party libraries
FetchContent_MakeAvailable(glfw)

# Create executable
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_SOURCE_DIR}/Source/*.h" "${CMAKE_SOURCE_DIR}/Source/*.cpp")
source_group("Source" "${CMAKE_SOURCE_DIR}/Source" ${SUBDIRECTORIES})
add_executable("Source" main.cpp ${SUBDIRECTORIES})

# Include directories and link libraries
target_include_directories("Source" PRIVATE "${CMAKE_SOURCE_DIR}/Source")

target_link_libraries("Source" PRIVATE glfw)
target_link_libraries("Source" PRIVATE d3d11.lib)
target_link_libraries("Source" PRIVATE d3dcompiler.lib)
target_link_libraries("Source" PRIVATE dxguid.lib)

# Debug and release flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions("Source" PUBLIC MY_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_definitions("Source" PUBLIC MY_RELEASE)
endif()

#Macro definitions
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_definitions("Source" PUBLIC RUNTIME_API=__declspec\(dllexport\))
	target_compile_definitions("Source" PUBLIC FORCEINLINE=__forceinline)
else()
	message(FATAL_ERROR "Unsupported compiler")
endif()