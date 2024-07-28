if(PROJECT_IS_TOP_LEVEL)
	set(CMAKE_CXX_STANDARD 11)
endif()

add_library(dchess STATIC
	chessboard.cpp 
	piece.cpp 
	position.cpp 
	pieces/pawn.cpp
	pieces/knight.cpp
	pieces/bishop.cpp
	pieces/rook.cpp
	pieces/queen.cpp
	pieces/king.cpp
)

target_sources(dchess 
	INTERFACE
		FILE_SET dchess_headers
			TYPE HEADERS 
			BASE_DIRS 
				"${CMAKE_CURRENT_BINARY_DIR}"
				"./include"
)

configure_file(
	"include/dchessversion.hpp.in" 
	"dchessversion.hpp"
	@ONLY 
)
