message("==>> Configuring...")
if(WIN32)
	set(CONFIG "-G \\\"MinGW Makefiles\\\"")
endif()
execute_process( # configuration
	COMMAND "${CMAKE_COMMAND}" ${CONFIG} -B build -S . -DTARTAN_TESTING=YES -DTARTAN_DOCS=NO
	WORKING_DIRECTORY "$ENV{REPO}"
)

file(MAKE_DIRECTORY "$ENV{REPO}/build")

message("==>> Building...")
execute_process( # building
	COMMAND "${CMAKE_COMMAND}" --build build
	WORKING_DIRECTORY "$ENV{REPO}"
)

message("==>> Testing...")
execute_process( # test 
	COMMAND "${CMAKE_CTEST_COMMAND}"
	WORKING_DIRECTORY "$ENV{REPO}/build"
	RESULT_VARIABLE CODE
)

if(NOT ${CODE} STREQUAL "0")
	message(FATAL_ERROR "==>> Tests failed.")
else()
	message("==>> Tests completed successfully!")
endif()
