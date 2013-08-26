file(GLOB NXLS_SOURCE *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(nxls ${NXLS_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(nxls ${PNIIO_PKG_LIBRARIES})
install(TARGETS nxls DESTINATION ${CMAKE_INSTALL_BINDIR})
