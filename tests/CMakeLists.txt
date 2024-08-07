set(CMAKE_CXX_STANDARD 11)

set(ONEFILE_TESTS
	whitePawn
	blackPawn
	position
	makeMove
	enPassant
	noPieceGetter
	bishop
	knight
	rook
	queen
	checkMove
	castling
	castling1
	scholarsMate
)

add_library(testutils STATIC
	testutils/testutils.cpp
)
target_sources(testutils
	INTERFACE
		FILE_SET testutils_headers
			TYPE HEADERS 
			BASE_DIRS 
				"./include"
)
target_link_libraries(testutils
	dchess
)

foreach(T ${ONEFILE_TESTS})
	add_executable(${T} 
		${T}.cpp
	)
	target_link_libraries(${T} testutils)
	add_test(NAME ${T}
		COMMAND ${T}
	)
endforeach()

# interactive play
add_executable(interactivePlay
		interactivePlay.cpp
)
target_link_libraries(interactivePlay testutils)
add_custom_target(iplay 
	COMMAND interactivePlay
)
