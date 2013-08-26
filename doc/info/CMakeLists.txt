
set(TEXI_SRC det2nx.texi detinfo.texi input_files.texi mcaops.texi
             nexus_path.texi nx2xml.texi nxcat.texi nxls.texi rois.texi
             xml2nx.texi)
set(INFO_SRC pnitools.txi)

add_custom_command(OUTPUT pnitools.info PRE_BUILD 
                  COMMAND makeinfo -o${CMAKE_CURRENT_BINARY_DIR}/pnitools.info ${INFO_SRC}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
                  )
add_custom_target(pnitool_info ALL SOURCES pnitools.info)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pnitools.info 
        DESTINATION ${CMAKE_INSTALL_INFODIR})
