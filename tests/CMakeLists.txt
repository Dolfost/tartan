set(CMAKE_CXX_STANDARD 11)

set(ONEFILE_TESTS
	whitePawn
	blackPawn
	position
	makeMove
	enPassant
)

add_library(testutils INTERFACE)
target_sources(testutils
	INTERFACE
		FILE_SET testutils_headers
			TYPE HEADERS 
			BASE_DIRS 
				"./include"
)

foreach(T ${ONEFILE_TESTS})
	add_executable(${T} 
		${T}.cpp
	)
	target_link_libraries(${T} dchess testutils)
	add_test(NAME ${T}
		COMMAND ${T}
	)
endforeach()

# interactive play
add_executable(interactivePlay
		interactivePlay.cpp
)
target_link_libraries(interactivePlay dchess testutils)
add_custom_target(iplay 
	COMMAND interactivePlay
)
