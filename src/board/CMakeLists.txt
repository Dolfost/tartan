add_library(board STATIC
	board.cpp 
	piece.cpp 
	position.cpp 
	turnMap.cpp 
	turn.cpp 
)

target_sources(board
	PUBLIC
		FILE_SET board_headers
			TYPE HEADERS 
			BASE_DIRS 
				"${CMAKE_CURRENT_BINARY_DIR}"
				"include"
)

target_compile_features(board PUBLIC cxx_std_${TARTAN_CXX_STANDARD})

if (NOT MSVC)
	target_compile_options(board PRIVATE
		-Wall -pedantic-errors -Wextra
	)
endif()

configure_file(
	"include/tartan/version.hpp.in" 
	"tartan/version.hpp"
	@ONLY 
)

