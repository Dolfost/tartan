add_library(chess STATIC
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

target_sources(chess
	PUBLIC
		FILE_SET chess_headers
			TYPE HEADERS 
			BASE_DIRS 
				"include"
)
# target_compile_features(chess PUBLIC cxx_std_17)

target_link_libraries(chess board)

if (NOT MSVC)
	target_compile_options(chess PRIVATE
		-Wall -pedantic-errors -Wextra
	)
endif()
