include(GNUInstallDirs)

install(TARGETS tt_board tt_chess tt_tartan
	EXPORT tartan
	FILE_SET HEADERS
)
install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/man/" 
	TYPE MAN
)
install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/html" 
	TYPE DOC
)

include(CMakePackageConfigHelpers)
install(EXPORT tartan 
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
	NAMESPACE tt::
)
write_basic_package_version_file(
	"${CMAKE_INSTALL_LIBDIR}/cmake/"
	COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
	tartanConfig.cmake.in tartanConfig.cmake
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/"
#	PATH_VARS vars
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/tartanConfig.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/"
)
