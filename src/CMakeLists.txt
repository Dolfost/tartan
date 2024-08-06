if(PROJECT_IS_TOP_LEVEL)
	set(CMAKE_CXX_STANDARD 11)
endif()

add_library(dchess STATIC
	chessboard.cpp 
	piece.cpp 
	position.cpp 
	turnMap.cpp 
	turn.cpp 
	pieces/pawn/pawn.cpp
	pieces/pawn/pawnTurn.cpp
	pieces/bishop/bishop.cpp
	pieces/bishop/bishopTurn.cpp
	pieces/knight/knight.cpp
	pieces/knight/knightTurn.cpp
	pieces/rook/rook.cpp
	pieces/rook/rookTurn.cpp
	pieces/queen/queen.cpp
	pieces/queen/queenTurn.cpp
	pieces/king/king.cpp
	pieces/king/kingTurn.cpp
)

target_sources(dchess 
	PUBLIC
		FILE_SET dchess_headers
			TYPE HEADERS 
			BASE_DIRS 
				"${CMAKE_CURRENT_BINARY_DIR}"
				"./include"
)

if (NOT MSVC)
	target_compile_options(dchess PRIVATE
		-Wall -pedantic-errors -Wextra
	)
endif()

configure_file(
	"include/dchess/version.hpp.in" 
	"dchess/version.hpp"
	@ONLY 
)
