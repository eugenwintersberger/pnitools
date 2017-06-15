set(FILES test.py)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_test(NAME detinfo:acceptance:test
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/detinfo
         COMMAND test.py)
