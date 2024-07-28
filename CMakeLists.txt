cmake_minimum_required(VERSION 3.25)

project(dchess
	LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH 
	"${CMAKE_CURRENT_SOURCE_SIR}/cmake"
)

include(version.cmake)

add_subdirectory(src)

