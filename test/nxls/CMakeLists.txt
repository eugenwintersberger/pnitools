set(FILES test.py nxls_test.xml)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_test(NAME "nxls::acceptance::test"
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/nxls
         COMMAND test.py)
