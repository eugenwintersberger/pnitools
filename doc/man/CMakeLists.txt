
set(MANPAGES det2nx.1 
             detinfo.1 
             mcaops.1 
             nxcat.1 
             nxls.1 
             xml2nx.1)
install(FILES ${MANPAGES} DESTINATION ${CMAKE_INSTALL_MANDIR})
