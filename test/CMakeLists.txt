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
                 )

set(CLI_TEST_PY_FILES check_output.py 
                      det2nx_test.py 
                      detinfo_test.py
                      mcaops_test.py 
                      nxcat_test.py 
                      nxls_test.py 
                      xml2nx_test.py 
                      detops_test.py
                      run_cli_test.py)

set(XML_FILES basic.xml detector.xml)

if("${CMAKE_FAMILY_VERSION}" STREQUAL "2.6")
    file(MAKE_DIRECTORY data)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/readme.txt
        ${CMAKE_CURRENT_BINARY_DIR}/data/readme.txt COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/download.sh
        ${CMAKE_CURRENT_BINARY_DIR}/data/download.sh COPYONLY)

    foreach(PYFILE ${CLI_TEST_PY_FILES})
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${PYFILE}"
            ${CMAKE_CURRENT_BINARY_DIR}/${PYFILE} COPYONLY)
    endforeach()

    foreach(XML_FILE ${XML_FILES})
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${XML_FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/${XML_FILE} COPYONLY)
    endforeach() 

else()
    file(COPY data DESTINATION .)
    file(COPY ${CLI_TEST_PY_FILES} DESTINATION .)
    file(COPY ${XML_FILES} DESTINATION .)
endif()

#===================extract the data an prepear for testing=================


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_executable(pnitoolstest ${TEST_SOURCES})
target_link_libraries(pnitoolstest common_objects ${CPPUNIT_PKG_LIBRARIES} ${PNIIO_PKG_LIBRARIES})
