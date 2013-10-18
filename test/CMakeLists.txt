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

set(CLI_TEST_PY_FILES check_output.py 
                      det2nx_test.py 
                      detinfo_test.py
                      mcaops_test.py 
                      nxcat_test.py 
                      nxls_test.py 
                      xml2nx_test.py 
                      run_cli_test.py)

set(TEST_DATA_ARCHIVES data/fio.tar.xz
                       data/cbf.tar.xz
                       data/nexus.tar.xz
                       data/tif.tar.xz)


if("${CMAKE_FAMILY_VERSION}" STREQUAL "2.6")
    file(MAKE_DIRECTORY data)
    foreach(ARCHIVE TEST_DATA_ARCHIVES)
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${ARCHIVE}"
            "${CMAKE_CURRENT_BINARY_DIR}/${ARCHIVE}" COPYONLY)
    endforeach()

    foreach(PYFILE CLI_TEST_FILES)
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${PYFILE}"
            ${CMAKE_CURRENT_BINARY_DIR})
    endforeach()
else()
    file(COPY data DESTINATION .)
    file(COPY ${CLI_TEST_PY_FILES} DESTINATION .)
endif()

#=======================extract the data an prepear for testing=================
foreach(ARCHIVE TEST_DATA_ARCHIVES)
    string(REPLACE ".tar.xz" "" DATA_DIR_NAME ${ARCHIVE})
    string(REPLACE ".xz" "" DATA_TAR_NAME ${ARCHIVE})
    add_custom_command(OUTPUT ${DATA_DIR_NAME} 
        COMMAND unxz ${ARCHIVE}
        COMMAND tar xf ${DATA_TAR_NAME})
endforeach()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_executable(pnitoolstest ${TEST_SOURCES})
target_link_libraries(pnitoolstest common_objects ${CPPUNIT_PKG_LIBRARIES} ${PNIIO_PKG_LIBRARIES})
