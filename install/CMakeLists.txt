include(GNUInstallDirs)

if(TARTAN_TARTAN)
	install(TARGETS tt_board tt_chess tt_tartan
		EXPORT tartan
		FILE_SET HEADERS
	)
endif()
if(TARTAN_DOCS)
	install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/out/html" 
		TYPE DOC
	)
	if(NOT WIN32)
		install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/out/man/" 
			TYPE MAN
		)
	endif()
endif()

include(CMakePackageConfigHelpers)
if(TARTAN_TARTAN)
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
endif()
