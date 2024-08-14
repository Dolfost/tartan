cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH 
	"${CMAKE_CURRENT_LIST_DIR}/cmake"
)

include(version)

project(tartan
	LANGUAGES CXX
	VERSION ${GIT_VERSION_TAG}
)

add_subdirectory(src)

if (PROJECT_IS_TOP_LEVEL)
	enable_testing()
	add_subdirectory(tests)
endif()
