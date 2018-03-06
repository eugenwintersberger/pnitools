set(SOURCES attribute_metadata_test.cpp
            dataset_metadata_test.cpp
            )

set_boost_test_definitions(SOURCES "Testing NXLS components")
add_executable(nxls_test ${SOURCES})
target_link_libraries(nxls_test common_objects
	                  nxls_static 
                      pniio
                      Boost::unit_test_framework
                      )

add_boost_logging_test("nxls:components:test" nxls_test ${CMAKE_CURRENT_BINARY_DIR})
