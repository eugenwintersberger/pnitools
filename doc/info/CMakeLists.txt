set(TEXI_SRC det2nx.texi 
             detinfo.texi 
             input_files.texi 
             mcaops.texi
             nexus_path.texi 
             nx2xml.texi 
             nxcat.texi 
             nxls.texi 
             rois.texi
             detops.texi
             numeric_ranges.texi
             xml2nx.texi 
             top_node.texi
            )
set(INFO_SRC pnitools.txi)

foreach(TEXI_FILE ${TEXI_SRC})
    configure_file(${TEXI_FILE} ${TEXI_FILE} COPYONLY)
endforeach()

configure_file(${INFO_SRC} ${INFO_SRC} COPYONLY)


add_subdirectory(pics)
add_custom_command(OUTPUT pnitools.info  
                  COMMAND makeinfo -o${CMAKE_CURRENT_BINARY_DIR}/pnitools.info ${INFO_SRC}
                  DEPENDS ${TEXI_SRC} ${INFO_SRC}
                  )
add_custom_command(OUTPUT "html/index.html"
                   COMMAND makeinfo --html -o${CMAKE_CURRENT_BINARY_DIR}/html ${INFO_SRC}
                   DEPENDS ${TEXI_SRC} ${INFO_SRC} ${IMAGE_SRC}
                   )
add_custom_command(OUTPUT pnitools.pdf 
                   COMMAND pdftex --output-directory=${CMAKE_CURRENT_BINARY_DIR} ${INFO_SRC}
                   COMMAND pdftex --output-directory=${CMAKE_CURRENT_BINARY_DIR} ${INFO_SRC}
                   DEPENDS ${TEXI_SRC} ${INFO_SRC}
                   )
add_custom_target(pnitool_info ALL SOURCES "pnitools.info" "pnitools.pdf" "html/index.html")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pnitools.info 
        DESTINATION ${CMAKE_INSTALL_INFODIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pnitools.pdf 
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/pnitools-doc")
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html 
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/pnitools-doc")
