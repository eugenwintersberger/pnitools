set(SOURCE nxtee.cpp utils.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(nxtee ${SOURCE})
target_link_libraries(nxtee ${PNIIO_PKG_LIBRARIES} common_objects)
install(TARGETS nxtee DESTINATION ${CMAKE_INSTALL_BINDIR})
