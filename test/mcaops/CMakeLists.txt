set(DATFILES test_sum.py
             test_min.py
             test_max.py
             fiodata.nxs
             total_sum.dat
             roi1_sum.dat
             roi2_sum.dat
             total_min.dat
             roi1_min.dat
             roi2_min.dat
             total_max.dat
             roi1_max.dat
             roi2_max.dat
    )


foreach(F ${DATFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_test(NAME "mcaops_sum_operation:acceptance:test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND python test_sum.py)

add_test(NAME "mcaops_min_operation:acceptance:test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND python test_min.py)

add_test(NAME "mcaops_max_operation:acceptance:test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND python test_max.py)
