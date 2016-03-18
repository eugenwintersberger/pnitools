set(FILES test.py nxls_test.xml)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_test(NAME "nxls::acceptance::test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND test.py)
