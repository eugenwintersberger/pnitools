set(MCAOPS_SOURCE #io.cpp 
                  mcaops.cpp 
                  io/data_provider.cpp
                  io/data_provider_factory.cpp
                  io/stdin_provider.cpp
                  io/index_generator.cpp
                  #mcaops_utils.cpp 
                  operation.cpp 
                  sum_operation.cpp
                  operation_factory.cpp
                  #rebin_operation.cpp 
                  #scale_operation.cpp
                  )

add_executable(mcaops ${MCAOPS_SOURCE})
target_link_libraries(mcaops common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS mcaops DESTINATION ${CMAKE_INSTALL_BINDIR})
