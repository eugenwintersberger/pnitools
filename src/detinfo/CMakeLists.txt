set(DETINFO_SOURCE detinfo.cpp
                   config.cpp
                   utils.cpp
                   detector_info.cpp
                   cbf_info_reader.cpp
                   tiff_info_reader.cpp
                   nexus_info_reader.cpp
                   detector_layout.cpp
                   output_formatter.cpp
                   simple_output_formatter.cpp
                   key_value_output_formatter.cpp
                   xml_output_formatter.cpp
                   csv_output_formatter.cpp
                   formatter_factory.cpp )

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    configure_file(detinfo.exe.manifest.in detinfo.exe.manifest @ONLY)
    list(APPEND DETINFO_SOURCE ${PROJECT_BINARY_DIR}/src/detinfo/detinfo.exe.manifest)
endif()

add_executable(detinfo ${DETINFO_SOURCE})
target_link_libraries(detinfo common_objects pniio)
install(TARGETS detinfo DESTINATION ${CMAKE_INSTALL_BINDIR})
