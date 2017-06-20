set(FILES global_test.py
          uniform_test.py
          linear_test.py
          gauss_test.py)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_test(NAME "datgen:acceptance:global_test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${PYTHON_EXECUTABLE} global_test.py)

add_test(NAME "datgen:accpentance:uniform_test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${PYTHON_EXECUTABLE} uniform_test.py)

add_test(NAME "datgen:acceptance:linear_test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${PYTHON_EXECUTABLE} linear_test.py)

add_test(NAME "datgen:acceptance:gauss_test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${PYTHON_EXECUTABLE} gauss_test.py)
