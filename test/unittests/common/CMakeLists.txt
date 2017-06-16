set(SOURCES string_utils_test.cpp 
            file_test.cpp
            file_list_parser_test.cpp
            column_test.cpp
            file_type_test.cpp
            roi_test.cpp
            file_queue_test.cpp
            )


add_executable(common_test ${SOURCES})
target_link_libraries(common_test common_objects 
                      pniio
                      Boost::unit_test_framework
                      )

add_test(NAME "Common-components-test" COMMAND common_test)

set(ALGOSRC sum_test.cpp
            average_test.cpp
            rebin_test.cpp
    )
set_source_files_properties(sum_test.cpp PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; \
                            BOOST_TEST_MODULE=testing common algorithms")
add_executable(algorithms_test ${ALGOSRC})
target_link_libraries(algorithms_test common_objects
                      ${PNIIO_PKG_LIBRARIES}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME "Common-algorithms-test" COMMAND algorithms_test)
