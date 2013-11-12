set(DETOPS_SOURCE detops.cpp config.cpp io_utils.cpp roi_utils.cpp)

add_executable(detops ${DETOPS_SOURCE})
target_link_libraries(detops common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS detops DESTINATION ${CMAKE_INSTALL_BINDIR})
