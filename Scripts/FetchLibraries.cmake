cmake_minimum_required (VERSION 3.26)

include(FetchContent)

# GLFW library
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.4
)