set(OPS_SOURCES main.cpp 
                sum_test.cpp
                max_test.cpp
                min_test.cpp 
                maxpos_test.cpp
                minpos_test.cpp
                rebin_test.cpp
                scale_test.cpp
                )


add_executable(mcaops_operations_test ${OPS_SOURCES} 
               $<TARGET_OBJECTS:mcaops_ops_objects>)
target_link_libraries(mcaops_operations_test 
                      common_objects 
                      pniio
                      Boost::unit_test_framework
                      )

add_test(NAME "mcaops:operations_test" 
         COMMAND mcaops_operations_test)
