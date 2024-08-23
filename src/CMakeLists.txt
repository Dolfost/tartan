set(TARTAN_CXX_STANDARD 17)

add_subdirectory(board)
add_subdirectory(chess)

add_library(tt_tartan INTERFACE)
target_link_libraries(tt_tartan 
	INTERFACE tt_board tt_chess
)
add_library(tt::tartan ALIAS tt_tartan)

set_target_properties(tt_tartan PROPERTIES
	OUTPUT_NAME tartan
	EXPORT_NAME tartan
)
