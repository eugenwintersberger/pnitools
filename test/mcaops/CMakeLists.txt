set(DATFILES common.py
             test_sum.py
             test_min.py
             test_max.py
             test_maxpos.py
             test_minpos.py
             test_average.py
             test_rebin.py
             test_rebin_with_channels.py
             test_scale.py
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
             total_argmax.dat
             roi1_argmax.dat
             roi2_argmax.dat
             total_argmin.dat
             roi1_argmin.dat
             roi2_argmin.dat
             total_average.dat
             roi1_average.dat
             roi2_average.dat
             total_rebin.dat
             roi1_rebin.dat
             roi2_rebin.dat
             total_rebin_norm.dat
             roi1_rebin_norm.dat
             roi2_rebin_norm.dat
             rebin_channels.dat
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

add_test(NAME "mcaops_maxpos_operation:acceptance:test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND python test_maxpos.py)

add_test(NAME "mcaops_minpos_operation:acceptance:test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND python test_minpos.py)

add_test(NAME "mcaops_average_operation:acceptance:test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND python test_average.py)

add_test(NAME "mcaops_rebin_operation:acceptance:test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND python test_rebin.py)

add_test(NAME "mcaops_rebin_channels_operation:acceptance:test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND python test_rebin_with_channels.py)

add_test(NAME "mcaops_scale_operation:acceptance:test"
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND python test_scale.py)

