include(GNUInstallDirs)

install(TARGETS tt_board
	EXPORT tt_board_export
	FILE_SET tt_board_headers
)
install(TARGETS tt_chess
	EXPORT tt_chess_export
	FILE_SET tt_chess_headers
)

install(EXPORT tt_board_export
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/board
	FILE board.cmake
	NAMESPACE tt::
)
install(EXPORT tt_chess_export
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/chess
	FILE chess.cmake
	NAMESPACE tt::
)
