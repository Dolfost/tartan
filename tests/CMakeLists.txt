set(CMAKE_CXX_STANDARD 11)

add_executable(pawn 
	pawn.cpp
)

target_link_libraries(pawn dchess)

add_test(NAME pawn
	COMMAND pawn
)
