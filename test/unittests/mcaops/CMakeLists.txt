set(OPS_SOURCES main.cpp 
                sum_test.cpp
                max_test.cpp
                min_test.cpp 
                maxpos_test.cpp
                minpos_test.cpp
                rebin_test.cpp
                )


add_executable(mcaops_operations_test ${OPS_SOURCES} 
               $<TARGET_OBJECTS:mcaops_ops_objects>)
target_link_libraries(mcaops_operations_test 
                      common_objects 
                      ${PNIIO_PKG_LIBRARIES}
                      ${Boost_LIBRARIES} 
                      )

add_test(NAME "mcaops:operations_test" 
         COMMAND mcaops_operations_test)
