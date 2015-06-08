set(SOURCES grid_generator_test.cpp            
            )


add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MODULE)
add_executable(datgen_test ${SOURCES} $<TARGET_OBJECTS:datgen_objects>)
target_link_libraries(datgen_test common_objects 
                      ${PNIIO_PKG_LIBRARIES}
                      ${Boost_LIBRARIES} 
                      )

add_test(NAME "datgen-components-test" COMMAND datgen_test)
