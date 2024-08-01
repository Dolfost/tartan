set(CMAKE_CXX_STANDARD 11)

set(ONEFILE_TESTS
	whitePawn
	blackPawn
	position
	makeMove
)

foreach(T ${ONEFILE_TESTS})
	add_executable(${T} 
		${T}.cpp
	)
	target_link_libraries(${T} dchess)
	add_test(NAME ${T}
		COMMAND ${T}
	)
endforeach()
