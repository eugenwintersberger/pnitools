set(DATFILES common.py
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

add_executable(mcaops_min_test mcaops_min_test.cpp 
                               $<TARGET_OBJECTS:test_config>)
target_link_libraries(mcaops_min_test
    pniio Boost::filesystem Boost::unit_test_framework)
add_boost_logging_test("mcaops_min_operation:acceptance:test"
                       mcaops_min_test
                       ${WORK_DIR})

add_executable(mcaops_max_test mcaops_max_test.cpp 
                               $<TARGET_OBJECTS:test_config>)
target_link_libraries(mcaops_max_test
    pniio Boost::filesystem Boost::unit_test_framework)
add_boost_logging_test("mcaops_max_operation:acceptance:test"
                       mcaops_max_test
                       ${WORK_DIR})

add_executable(mcaops_minpos_test mcaops_minpos_test.cpp 
                               $<TARGET_OBJECTS:test_config>)
target_link_libraries(mcaops_minpos_test
    pniio Boost::filesystem Boost::unit_test_framework)
add_boost_logging_test("mcaops_minpos_operation:acceptance:test"
                       mcaops_minpos_test
                       ${WORK_DIR})

add_executable(mcaops_maxpos_test mcaops_maxpos_test.cpp 
                               $<TARGET_OBJECTS:test_config>)
target_link_libraries(mcaops_maxpos_test
    pniio Boost::filesystem Boost::unit_test_framework)
add_boost_logging_test("mcaops_maxpos_operation:acceptance:test"
                       mcaops_maxpos_test
                       ${WORK_DIR})

add_executable(mcaops_average_test mcaops_average_test.cpp 
                               $<TARGET_OBJECTS:test_config>)
target_link_libraries(mcaops_average_test
    pniio Boost::filesystem Boost::unit_test_framework)
add_boost_logging_test("mcaops_average_operation:acceptance:test"
                       mcaops_average_test
                       ${WORK_DIR})

add_executable(mcaops_rebin_test mcaops_rebin_test.cpp
                                 $<TARGET_OBJECTS:test_config>)
target_link_libraries(mcaops_rebin_test
    pniio Boost::filesystem Boost::unit_test_framework)
add_boost_logging_test("mcaops_rebin_operation:acceptance:test"
                       mcaops_rebin_test
                       ${WORK_DIR})


add_test(NAME "mcaops_rebin_channels_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_rebin_with_channels.py)

add_test(NAME "mcaops_scale_operation:acceptance:test"
         WORKING_DIRECTORY ${WORK_DIR}
         COMMAND ${PYTHON_EXECUTABLE} test_scale.py)
