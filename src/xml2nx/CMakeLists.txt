file(GLOB XML2NX_SOURCE *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(xml2nx ${XML2NX_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(xml2nx ${PNIIO_PKG_LIBRARIES})
install(TARGETS xml2nx DESTINATION ${CMAKE_INSTALL_BINDIR})
