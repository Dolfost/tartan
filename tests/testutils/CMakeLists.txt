add_library(testutils STATIC
	testutils.cpp
)


target_sources(testutils
	INTERFACE
		FILE_SET testutils_headers
			TYPE HEADERS 
			BASE_DIRS 
				"./include"
)

target_link_libraries(testutils
	tt::chess
)
