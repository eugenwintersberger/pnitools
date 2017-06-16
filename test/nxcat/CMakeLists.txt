set(FILES test.py)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_test(NAME "nxcat:acceptance:test"
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/nxcat
         COMMAND test.py)
