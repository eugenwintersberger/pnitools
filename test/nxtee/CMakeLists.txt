set(FILES mca.xml test.py )

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_test(NAME "nxtee:acceptance:test"
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/nxtee
         COMMAND ${PYTHON_EXECUTABLE} test.py)
