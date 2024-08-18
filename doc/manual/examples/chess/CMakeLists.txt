add_executable(complexGame
	complexGame.cpp 
)
target_link_libraries(complexGame
	board chess 
)

add_executable(game
	game.cpp 
)
target_link_libraries(game
	board chess 
)
