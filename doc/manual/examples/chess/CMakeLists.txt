add_executable(complexGame
	complexGame.cpp 
)
target_link_libraries(complexGame
	tt::board tt::chess 
)

add_executable(game
	game.cpp 
)
target_link_libraries(game
	tt::board tt::chess 
)
