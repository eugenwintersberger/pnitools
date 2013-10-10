
set(TEXI_SRC det2nx.texi 
             detinfo.texi 
             input_files.texi 
             mcaops.texi
             nexus_path.texi 
             nx2xml.texi 
             nxcat.texi 
             nxls.texi 
             rois.texi
             xml2nx.texi 
             pics/mcaops_testdata.txt
             pics/gnuplot.pdf
             pics/mca_basics_1.pdf
             pics/mcaops_rebin3.pdf
             pics/mcaops_testdata.pdf
             pics/nxcat_full.pdf
             pics/nxcat_selection.pdf
             )

set(INFO_SRC pnitools.txi)

add_custom_command(OUTPUT pnitools.info  
                  COMMAND makeinfo -o${CMAKE_CURRENT_BINARY_DIR}/pnitools.info ${INFO_SRC}
                  DEPENDS ${TEXI_SRC} ${INFO_SRC}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                  )
add_custom_command(OUTPUT pnitools.pdf 
                   COMMAND pdftex --output-directory=${CMAKE_CURRENT_BINARY_DIR} ${INFO_SRC}
                   COMMAND pdftex --output-directory=${CMAKE_CURRENT_BINARY_DIR} ${INFO_SRC}
                   DEPENDS ${TEXI_SRC} ${INFO_SRC}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   )
add_custom_target(pnitool_info ALL SOURCES "pnitools.info" "pnitools.pdf")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pnitools.info 
        DESTINATION ${CMAKE_INSTALL_INFODIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pnitools.pdf
        DESTINATION "${CMAKE_INSTALL_DOCDIR}/pnitools-doc")
