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

set(WORK_DIR ${PROJECT_BINARY_DIR}/test/mcaops)

add_executable(mcaops_sum_test mcaops_sum_operation.cpp 
                               $<TARGET_OBJECTS:test_config>)
target_link_libraries(mcaops_sum_test 
    pniio Boost::filesystem Boost::unit_test_framework)

add_boost_logging_test("mcaops_sum_operation:acceptance:test"
                       mcaops_sum_test
                       ${WORK_DIR})


add_test(NAME "mcaops_min_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_min.py)

add_test(NAME "mcaops_max_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_max.py)

add_test(NAME "mcaops_maxpos_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_maxpos.py)

add_test(NAME "mcaops_minpos_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_minpos.py)

add_test(NAME "mcaops_average_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_average.py)

add_test(NAME "mcaops_rebin_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_rebin.py)

add_test(NAME "mcaops_rebin_channels_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_rebin_with_channels.py)

add_test(NAME "mcaops_scale_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_scale.py)
