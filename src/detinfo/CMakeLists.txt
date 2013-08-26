file(GLOB DETINFO_SOURCE *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(detinfo ${DETINFO_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(detinfo ${PNIIO_PKG_LIBRARIES})
install(TARGETS detinfo DESTINATION ${CMAKE_INSTALL_BINDIR})
