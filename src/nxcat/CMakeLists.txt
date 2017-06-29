set(NXCAT_SOURCE nxcat.cpp nxcat_util.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    configure_file(nxcat.exe.manifest.in nxcat.exe.manifest @ONLY)
    list(APPEND NXCAT_SOURCE
        ${PROJECT_BINARY_DIR}/src/nxcat/nxcat.exe.manifest)
endif()

add_executable(nxcat ${NXCAT_SOURCE})
target_link_libraries(nxcat common_objects pniio)
install(TARGETS nxcat DESTINATION ${CMAKE_INSTALL_BINDIR})
