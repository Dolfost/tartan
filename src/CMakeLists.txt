set(TARTAN_CXX_STANDARD 17)

add_subdirectory(board)
add_subdirectory(chess)

add_library(tartan INTERFACE)
target_link_libraries(tartan 
	INTERFACE board chess
)
