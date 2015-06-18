
set(MANPAGES datgen.1
             det2nx.1
             detinfo.1
             detops.1
             mcaops.1
             nxcat.1
             nxls.1
             xml2nx.1
            )


foreach(F ${MANPAGES})
    configure_file(${F} ${F} @ONLY)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${F}
            DESTINATION "${CMAKE_INSTALL_MANDIR}/man1")
endforeach()

