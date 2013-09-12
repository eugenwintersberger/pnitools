set(TEST_SOURCES pnitoolstest.cpp 
                 common/array_utils_test.cpp 
                 common/file_list_parser_test.cpp 
                 common/file_test.cpp
                 common/column_test.cpp)

file(COPY data DESTINATION .)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_executable(pnitoolstest ${TEST_SOURCES})
target_link_libraries(pnitoolstest common_objects ${CPPUNIT_PKG_LIBRARIES} ${PNIIO_PKG_LIBRARIES})
