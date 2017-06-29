set(XML2NX_SOURCE xml2nx.cpp xml2nx_utils.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    configure_file(xml2nx.exe.manifest.in xml2nx.exe.manifest @ONLY)
    list(APPEND XML2NX_SOURCE
        ${PROJECT_BINARY_DIR}/src/xml2nx/xml2nx.exe.manifest)
endif()

add_executable(xml2nx ${XML2NX_SOURCE})
target_link_libraries(xml2nx common_objects pniio)
install(TARGETS xml2nx DESTINATION ${CMAKE_INSTALL_BINDIR})
