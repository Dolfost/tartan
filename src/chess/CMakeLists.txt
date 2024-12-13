add_library(tt_chess STATIC
	chess.cpp
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
add_library(tt::chess ALIAS tt_chess)

set_target_properties(tt_chess PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
	OUTPUT_NAME ttchess
	EXPORT_NAME chess
)

target_sources(tt_chess
	PUBLIC FILE_SET HEADERS
		BASE_DIRS "include"
		FILES
			include/tartan/chess.hpp
			include/tartan/chess/chess.hpp
			include/tartan/chess/exceptions.hpp
)

target_link_libraries(tt_chess tt_board)

if (NOT MSVC)
	target_compile_options(tt_chess PRIVATE
		-Wall -pedantic-errors -Wextra
	)
endif()
