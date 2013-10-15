set(TEST_SOURCES pnitoolstest.cpp 
                 common/array_utils_test.cpp 
                 common/file_list_parser_test.cpp 
                 common/file_test.cpp
                 common/column_test.cpp
                 mcaops/sum_operation_test.cpp
                 mcaops/max_operation_test.cpp
                 mcaops/scale_operation_test.cpp
                 mcaops/rebin_operation_test.cpp
                 compare.cpp
                 ../src/mcaops/operation.cpp
                 ../src/mcaops/scale_operation.cpp
                 ../src/mcaops/rebin_operation.cpp
                 type_id.cpp)

if("${CMAKE_FAMILY_VERSION}" STREQUAL "2.6")
    file(MAKE_DIRECTORY data)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/fio.tar.xz
        ${CMAKE_CURRENT_BINARY_DIR}/data/fio.tar.xz COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/cbf.tar.xz
        ${CMAKE_CURRENT_BINARY_DIR}/data/cbf.tar.xz COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/tif.tar.xz
        ${CMAKE_CURRENT_BINARY_DIR}/data/tif.tar.xz COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/nexus.tar.xz
        ${CMAKE_CURRENT_BINARY_DIR}/data/nexus.tar.xz COPYONLY)
else()
    file(COPY data DESTINATION .)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_executable(pnitoolstest ${TEST_SOURCES})
target_link_libraries(pnitoolstest common_objects ${CPPUNIT_PKG_LIBRARIES} ${PNIIO_PKG_LIBRARIES})
