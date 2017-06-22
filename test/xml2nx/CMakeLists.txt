set(FILES test.py basic.xml detector.xml)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_executable(xml2nx_acceptance_test test.cpp $<TARGET_OBJECTS:test_config>)
target_link_libraries(xml2nx_acceptance_test
    pniio Boost::unit_test_framework Boost::filesystem)

add_boost_logging_test("xml2nx:acceptance:test" xml2nx_acceptance_test
                       ${PROJECT_BINARY_DIR}/test/xml2nx)
