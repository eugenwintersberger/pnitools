set(SOURCE nxtee.cpp utils.cpp operation.cpp selection.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    configure_file(nxtee.exe.manifest.in nxtee.exe.manifest @ONLY)
    list(APPEND SOURCE ${PROJECT_BINARY_DIR}/src/nxtee/nxtee.exe.manifest)
endif()

add_executable(nxtee ${SOURCE})
target_link_libraries(nxtee pniio common_objects)
install(TARGETS nxtee DESTINATION ${CMAKE_INSTALL_BINDIR})
