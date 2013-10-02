set(XML2NX_SOURCE xml2nx.cpp xml2nx_utils.cpp)

add_executable(xml2nx ${XML2NX_SOURCE})
target_link_libraries(xml2nx common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS xml2nx DESTINATION ${CMAKE_INSTALL_BINDIR})
