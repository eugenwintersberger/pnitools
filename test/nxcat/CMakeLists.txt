
add_executable(nxcat_acceptance_test test.cpp $<TARGET_OBJECTS:test_config>)
target_link_libraries(nxcat_acceptance_test
    pniio Boost::unit_test_framework Boost::filesystem)

add_boost_logging_test("nxcat:acceptance:test"
                       nxcat_acceptance_test
                       ${PROJECT_BINARY_DIR}/test/nxcat)
