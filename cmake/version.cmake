find_package(Git QUIET)

set(GIT_VERSION_TAG_FAILED FALSE)
macro(fallback MSG)
	message(WARNING "${MSG}")
	message(WARNING "Setting GIT_VERSION_TAG to 0.1.1.0")
	set(GIT_VERSION_TAG 0.1.1.0)
	set(GIT_VERSION_TAG_FAILED TRUE)
endmacro()

if(GIT_FOUND)
	execute_process(
		COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
		OUTPUT_VARIABLE GIT_VERSION_TAG
		WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
		RESULT_VARIABLE RESULT
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	if(RESULT EQUAL 0)
		string(REGEX REPLACE 
			"^v?([0-9]+\\.[0-9]+\\.?[0-9]*\\.?[0-9]*).*$"
			"\\1"
			GIT_VERSION_TAG
			${GIT_VERSION_TAG}
		)
	else()
		fallback(
[[ 
Git returned ${RESULT}. Maybe repository is clonned shallowly.
Try to execute git pull --tags if so.
]]
		)
	endif()
else()
	fallback("Git wasn't found")
endif()

# do cmake -DGIT_VERSION_TESTING=YES -P version.cmake for test
if (GIT_VERSION_TESTING)
	if (GIT_VERSION_TAG_FAILED)
		message("Failed to extract git version tag, using fallback value: '${GIT_VERSION_TAG}'")
	else()
		message("Extracted git version tag: '${GIT_VERSION_TAG}'")
	endif()
endif()
