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
	checkmate1
	checkmate2
	check1
	noEnPassant
)

add_subdirectory(testutils)

foreach(T ${ONEFILE_TESTS})
	add_executable(${T} 
		${T}.cpp
	)
	set_property(TARGET ${T} PROPERTY
		CXX_STANDARD ${${PROJECT_NAME}_CXX_STANDARD}
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
