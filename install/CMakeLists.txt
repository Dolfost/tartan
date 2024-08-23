include(GNUInstallDirs)

install(TARGETS tt_borad
	EXPORT tt_board_export
)
install(TARGETS tt_chess
	EXPORT tt_chess_export
)

install(EXPORT tt_board_export
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/board
	NAMESPACE tt::
)
install(EXPORT tt_chess_export
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/chess
	NAMESPACE tt::
)
