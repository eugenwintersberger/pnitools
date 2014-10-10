
set(MAN_SRC det2nx.1.cmake
            detinfo.1.cmake
            mcaops.1.cmake
            nxcat.1.cmake
            nxls.1.cmake
            xml2nx.1.cmake
            )

set(MANPAGES)

foreach(SRC_FILE ${MAN_SRC})
    string(REPLACE ".cmake" "" MAN_FILE ${SRC_FILE})
    configure_file(${SRC_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${MAN_FILE} @ONLY)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${MAN_FILE}
            DESTINATION "${CMAKE_INSTALL_MANDIR}/man1")
endforeach()

