set(NXCAT_SOURCE nxcat.cpp nxcat_util.cpp)

add_executable(nxcat ${NXCAT_SOURCE})
target_link_libraries(nxcat common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS nxcat DESTINATION ${CMAKE_INSTALL_BINDIR})
