set(DETINFO_SOURCE detinfo.cpp 
                   config.cpp 
                   utils.cpp 
                   detector_info.cpp
                   cbf_info_reader.cpp
                   tiff_info_reader.cpp
                   nexus_info_reader.cpp
                   detector_layout.cpp
                   output_formatter.cpp
                   text_output_formatter.cpp
                   key_value_output_formatter.cpp
                   formatter_factory.cpp )

add_executable(detinfo ${DETINFO_SOURCE})
target_link_libraries(detinfo common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS detinfo DESTINATION ${CMAKE_INSTALL_BINDIR})
