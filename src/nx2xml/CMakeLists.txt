file(GLOB NX2XML_SOURCE *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(nx2xml ${NX2XML_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(nx2xml ${PNIIO_PKG_LIBRARIES})
install(TARGETS nx2xml DESTINATION ${CMAKE_INSTALL_BINDIR})
