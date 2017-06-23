set(FILES 
                    linear_test.py
          gauss_test.py)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_library(datgen_common OBJECT datgen_fixture.cpp)

add_executable(global_test global_test.cpp 
                           $<TARGET_OBJECTS:test_config>
                           $<TARGET_OBJECTS:datgen_common>)
target_link_libraries(global_test 
    pniio Boost::unit_test_framework Boost::filesystem)

add_boost_logging_test("datgen:acceptance:global_test"
                       global_test
                       ${PROJECT_BINARY_DIR}/test/datgen)


add_executable(uniform_test uniform_test.cpp
                            $<TARGET_OBJECTS:test_config>
                            $<TARGET_OBJECTS:datgen_common>)
target_link_libraries(uniform_test
    pniio Boost::unit_test_framework Boost::filesystem)
add_boost_logging_test("datgen:acceptance:uniform_test"
                       uniform_test
                       ${PROJECT_BINARY_DIR}/test/datgen)

add_executable(linear_test linear_test.cpp
                           $<TARGET_OBJECTS:test_config>
                           $<TARGET_OBJECTS:datgen_common>)
target_link_libraries(linear_test
    pniio Boost::unit_test_framework Boost::filesystem)
add_boost_logging_test("datgen:acceptance:linear_test"
                       linear_test
                       ${PROJECT_BINARY_DIR}/test/datgen)


add_test(NAME "datgen:acceptance:gauss_test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${PYTHON_EXECUTABLE} gauss_test.py)
