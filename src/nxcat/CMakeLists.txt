file(GLOB NXCAT_SOURCE *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(nxcat ${NXCAT_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(nxcat ${PNIIO_PKG_LIBRARIES})
install(TARGETS nxcat DESTINATION ${CMAKE_INSTALL_BINDIR})
