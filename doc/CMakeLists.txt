add_subdirectory("source")

configure_file(SphinxMakefile SphinxMakefile COPYONLY)
configure_file(Doxyfile Doxyfile @ONLY)
configure_file(DoxygenLayout.xml DoxygenLayout.xml COPYONLY)
configure_file(doxygroups.dox doxygroups.dox COPYONLY)

#add_custom_target(xml_doc ALL
#                  COMMAND doxygen
#                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#                  COMMENT "Building XML documentation from sources")

#here we have to build the code
add_custom_target(html_doc ALL
                  COMMAND make -fSphinxMakefile html
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT Building html documentation)

add_custom_target(pdf_doc ALL
                  COMMAND make -fSphinxMakefile latexpdf
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT Building PDF documentation)

add_custom_target(man_doc ALL
                  COMMAND make -fSphinxMakefile man
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT Building manpages)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build/html 
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/pnitools-doc)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/build/latex/PNITools.pdf
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/pnitools-doc)

set(MANPAGES ${CMAKE_CURRENT_BINARY_DIR}/build/man/detinfo.1
             ${CMAKE_CURRENT_BINARY_DIR}/build/man/mcaops.1
             ${CMAKE_CURRENT_BINARY_DIR}/build/man/nxcat.1
             ${CMAKE_CURRENT_BINARY_DIR}/build/man/nxls.1
             ${CMAKE_CURRENT_BINARY_DIR}/build/man/nxtee.1
             ${CMAKE_CURRENT_BINARY_DIR}/build/man/xml2nx.1
             )

install(FILES ${MANPAGES}
        DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

