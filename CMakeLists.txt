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

if (NOT DEFINED TARTAN_DOCS AND 
	PROJECT_IS_TOP_LEVEL OR TARTAN_DOCS)
	add_subdirectory(doc)
endif()

if (NOT DEFINED TARTAN_TESTING AND 
	PROJECT_IS_TOP_LEVEL OR TARTAN_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()
