set(MCAOPS_SOURCE #io.cpp
                  mcaops.cpp
                  command_predicate.cpp
                  utils.cpp
                  #mcaops_utils.cpp
                  #rebin_operation.cpp
                  #scale_operation.cpp
                  )

add_subdirectory(io)
add_subdirectory(operations)
add_executable(mcaops ${MCAOPS_SOURCE} 
                      )
target_link_libraries(mcaops common_objects mcaops_io mcaops_ops pniio)

install(TARGETS mcaops DESTINATION ${CMAKE_INSTALL_BINDIR})
