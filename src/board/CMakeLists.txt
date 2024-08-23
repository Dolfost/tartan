add_library(tt_board STATIC
	board.cpp 
	piece.cpp 
	position.cpp 
	turnMap.cpp 
	turn.cpp 
)
add_library(tt::board ALIAS tt_board)

set_target_properties(tt_board PROPERTIES
	OUTPUT_NAME board
	EXPORT_NAME board
)

target_sources(tt_board
	PUBLIC
		FILE_SET tt_board_headers
			TYPE HEADERS 
			BASE_DIRS 
				"${CMAKE_CURRENT_BINARY_DIR}"
				"include"
)

target_compile_features(tt_board PUBLIC cxx_std_${TARTAN_CXX_STANDARD})

if (NOT MSVC)
	target_compile_options(tt_board PRIVATE
		-Wall -pedantic-errors -Wextra
	)
endif()

configure_file(
	"include/tartan/version.hpp.in" 
	"tartan/version.hpp"
	@ONLY 
)

