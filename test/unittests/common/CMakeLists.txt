set(SOURCES string_utils_test.cpp 
            file_test.cpp
            file_list_parser_test.cpp
            column_test.cpp
            file_type_test.cpp
            )


add_executable(common_test ${SOURCES})
target_link_libraries(common_test common_objects 
                      ${PNIIO_PKG_LIBRARIES}
                      ${Boost_LIBRARIES} 
                      )

add_test(NAME "Common-components-test" COMMAND common_test)
