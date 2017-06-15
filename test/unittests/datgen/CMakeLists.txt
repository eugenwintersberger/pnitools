set(SOURCES grid_generator_test.cpp
            grid_generator_builder_test.cpp
            main.cpp
            utils_test.cpp
            option_splitter_test.cpp
            linear_functor_test.cpp
            gauss_functor_test.cpp
            )


add_executable(datgen_test ${SOURCES} $<TARGET_OBJECTS:datgen_functor_objects>
                                      $<TARGET_OBJECTS:datgen_objects>
    )
target_link_libraries(datgen_test common_objects
                      pniio
                      ${Boost_LIBRARIES}
                      )

add_test(NAME "datgen-components-test" COMMAND datgen_test)
