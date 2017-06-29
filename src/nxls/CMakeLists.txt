set(NXLS_SOURCE nxls.cpp
                config.cpp
                utils.cpp
                output_config.cpp
                output.cpp
                )

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    configure_file(nxls.exe.manifest.in nxls.exe.manifest @ONLY)
    list(APPEND NXLS_SOURCE ${PROJECT_BINARY_DIR}/src/nxls/nxls.exe.manifest)
endif()

add_executable(nxls ${NXLS_SOURCE})
target_link_libraries(nxls common_objects pniio)
install(TARGETS nxls DESTINATION ${CMAKE_INSTALL_BINDIR})
