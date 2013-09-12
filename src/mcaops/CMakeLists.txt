set(MCAOPS_SOURCE io.cpp mcaops.cpp mcaops_utils.cpp operation.cpp 
                  rebin_operation.cpp scale_operation.cpp)

add_executable(mcaops ${MCAOPS_SOURCE})
target_link_libraries(mcaops common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS mcaops DESTINATION ${CMAKE_INSTALL_BINDIR})
