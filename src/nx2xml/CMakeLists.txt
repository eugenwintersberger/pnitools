set(NX2XML_SOURCE nx2xml.cpp nx2xml_utils.cpp xml_utils.cpp)

add_executable(nx2xml ${NX2XML_SOURCE})
target_link_libraries(nx2xml common_objects pniio)
install(TARGETS nx2xml DESTINATION ${CMAKE_INSTALL_BINDIR})
