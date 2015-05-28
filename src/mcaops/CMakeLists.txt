set(MCAOPS_SOURCE #io.cpp 
                  mcaops.cpp 
                  command_predicate.cpp
                  #mcaops_utils.cpp 
                  #rebin_operation.cpp 
                  #scale_operation.cpp
                  )

add_subdirectory(io)
add_subdirectory(operations)
add_executable(mcaops $<TARGET_OBJECTS:mcaops_io> 
                      $<TARGET_OBJECTS:mcaops_ops>
                      ${MCAOPS_SOURCE} )
target_link_libraries(mcaops common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS mcaops DESTINATION ${CMAKE_INSTALL_BINDIR})
