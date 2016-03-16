add_subdirectory("source")

configure_file(SphinxMakefile SphinxMakefile COPYONLY)
configure_file(Doxyfile Doxyfile @ONLY)
configure_file(DoxygenLayout.xml DoxygenLayout.xml COPYONLY)
configure_file(doxygroups.dox doxygroups.dox COPYONLY)

#here we have to build the code
add_custom_target(html_doc 
                  COMMAND make -fSphinxMakefile html
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT Building html documentation)

add_custom_target(man_doc ALL
                  COMMAND make -fSphinxMakefile man
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT Building manpages)
