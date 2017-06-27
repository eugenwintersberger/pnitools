set(SOURCES test.cpp)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    set(LASTSEP "\\")
else()
    set(LASTSEP "/")
endif()


configure_file(cbf_simple_output.pattern.in cbf_simple_output.pattern @ONLY)
configure_file(nexus_simple_output.pattern.in nexus_simple_output.pattern @ONLY)
configure_file(tif_simple_output.pattern.in tif_simple_output.pattern @ONLY)
configure_file(cbf_kv_output.pattern.in cbf_kv_output.pattern @ONLY)
configure_file(nexus_kv_output.pattern.in nexus_kv_output.pattern @ONLY)
configure_file(tif_kv_output.pattern.in tif_kv_output.pattern @ONLY)
configure_file(cbf_csv_output.pattern.in cbf_csv_output.pattern @ONLY)
configure_file(nexus_csv_output.pattern.in nexus_csv_output.pattern @ONLY)
configure_file(tif_csv_output.pattern.in tif_csv_output.pattern @ONLY)
configure_file(cbf_xml_output.pattern.in cbf_xml_output.pattern @ONLY)
configure_file(nexus_xml_output.pattern.in nexus_xml_output.pattern @ONLY)
configure_file(tif_xml_output.pattern.in tif_xml_output.pattern @ONLY)

add_executable(detinfo_acceptance_test test.cpp $<TARGET_OBJECTS:test_config>)
target_link_libraries(detinfo_acceptance_test PRIVATE
Boost::unit_test_framework Boost::filesystem pniio)


add_boost_logging_test("detinfo:acceptance:test"
                       detinfo_acceptance_test
                       ${PROJECT_BINARY_DIR}/test/detinfo)
