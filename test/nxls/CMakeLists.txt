set(FILES nxls_test.xml)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_executable(nxls_acceptance_test test.cpp $<TARGET_OBJECTS:test_config>)
target_link_libraries(nxls_acceptance_test 
    pniio Boost::filesystem Boost::unit_test_framework)

add_boost_logging_test("nxls:acceptance:test"
                       nxls_acceptance_test 
                       ${PROJECT_BINARY_DIR}/test/nxls)
