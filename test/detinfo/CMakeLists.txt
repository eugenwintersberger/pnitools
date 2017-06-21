set(SOURCES test.cpp)

configure_file(ref_data.hpp.in ref_data.hpp @ONLY)

add_executable(detinfo_acceptance_test test.cpp $<TARGET_OBJECTS:test_config>)
target_link_libraries(detinfo_acceptance_test PRIVATE
Boost::unit_test_framework Boost::filesystem pniio)


add_boost_logging_test("detinfo:acceptance:test"
                       detinfo_acceptance_test
                       ${PROJECT_BINARY_DIR}/test/detinfo)
