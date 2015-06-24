set(FILES global_test.py
          uniform_test.py
          linear_test.py
          gauss_test.py)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_test(NAME "datgen:global_test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND global_test.py)

add_test(NAME "datgen:uniform_test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND uniform_test.py)

add_test(NAME "datgen:linear_test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND linear_test.py)

add_test(NAME "datgen:gauss_test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND gauss_test.py)
