cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH 
	"${CMAKE_CURRENT_LIST_DIR}/cmake"
)

include(version)

project(tartan
	LANGUAGES CXX
	VERSION ${GIT_VERSION_TAG}
	DESCRIPTION "Chess API"
)

option(TARTAN_TARTAN 
	"Build library"
	YES
)
option(TARTAN_DOCS
	"Build library documentation"
	${PROJECT_IS_TOP_LEVEL}
)
option(TARTAN_TESTING
	"Build test scripts"
	${PROJECT_IS_TOP_LEVEL}
)

if (TARTAN_TARTAN)
	add_subdirectory(src)
endif()

if (TARTAN_DOCS)
	add_subdirectory(doc)
endif()

if (TARTAN_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()

add_subdirectory(install)

if(PROJECT_IS_TOP_LEVEL)
	add_subdirectory(packaging)
endif()
