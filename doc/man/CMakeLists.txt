
configure_file(det2nx.1.cmake det2nx.1 @ONLY)
configure_file(detinfo.1.cmake detinfo.1 @ONLY)
configure_file(mcaops.1.cmake mcaops.1 @ONLY)
configure_file(nxcat.1.cmake nxcat.1 @ONLY)
configure_file(nxls.1.cmake nxls.1 @ONLY)
configure_file(xml2nx.1.cmake xml2nx.1 @ONLY)

set(MANPAGES ${CMAKE_CURRENT_BINARY_DIR}/det2nx.1 
             ${CMAKE_CURRENT_BINARY_DIR}/detinfo.1 
             ${CMAKE_CURRENT_BINARY_DIR}/mcaops.1 
             ${CMAKE_CURRENT_BINARY_DIR}/nxcat.1 
             ${CMAKE_CURRENT_BINARY_DIR}/nxls.1 
             ${CMAKE_CURRENT_BINARY_DIR}/xml2nx.1)
install(FILES ${MANPAGES} DESTINATION "${CMAKE_INSTALL_MANDIR}/man1")
