set(DET2NX_SOURCE det2nx.cpp config.cpp utils.cpp)

add_executable(det2nx ${DET2NX_SOURCE})
target_link_libraries(det2nx common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS det2nx DESTINATION "${CMAKE_INSTALL_BINDIR}")
