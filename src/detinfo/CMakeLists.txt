set(DETINFO_SOURCE detinfo.cpp)

add_executable(detinfo ${DETINFO_SOURCE})
target_link_libraries(detinfo common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS detinfo DESTINATION ${CMAKE_INSTALL_BINDIR})
