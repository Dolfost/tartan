set(CMAKE_CXX_STANDARD 11)

set(ONEFILE_TESTS
	pawn
	position
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
