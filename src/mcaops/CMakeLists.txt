file(GLOB MCAOPS_SOURCE *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(mcaops ${MCAOPS_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(mcaops ${PNIIO_PKG_LIBRARIES})
install(TARGETS mcaops DESTINATION ${CMAKE_INSTALL_BINDIR})
