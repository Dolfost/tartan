find_package(Doxygen
	REQUIRED dot doxygen
	OPTIONAL_COMPONENTS mscgen dia
)

get_target_property(DOC_SRC tartan SOURCE_DIR)

set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN YES)
set(DOXYGEN_GENERATE_LATEX YES)
set(DOXYGEN_INTERACTIVE_SVG YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_GENERATE_TREEVIEW YES)

set(DOXYGEN_IMAGE_PATH images/)
set(DOXYGEN_DOT_IMAGE_FORMAT svg)
set(DOXYGEN_CITE_BIB_FILES
	bibliography/games.bib
	bibliography/tools.bib
)
set(DOXYGEN_TAGFILES
	"cppreference-doxygen-web.tag.xml=https://en.cppreference.com/w/"
)

cmake_path(ABSOLUTE_PATH DOC_SRC
	BASE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	OUTPUT_VARIABLE PSTRIP
)
set(DOXYGEN_STRIP_FROM_PATH ${PSTRIP})
	
# set(DOXYGEN_PROJECT_LOGO 
# 	"${DOXYGEN_IMAGE_PATH}/logo.png"
# )
# set(DOXYGEN_PROJECT_LOGO 
# 	"${DOXYGEN_IMAGE_PATH}/icon.png"
# )

doxygen_add_docs(doc ALL
	"${DOC_SRC}" manual/
	WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
