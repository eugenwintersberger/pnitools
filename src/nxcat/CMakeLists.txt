file(GLOB NXCAT_SOURCE *.cpp)

add_executable(nxcat ${NXCAT_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(nxcat ${PNIIO_PKG_LIBRARIES})
install(TARGETS nxcat DESTINATION ${CMAKE_INSTALL_BINDIR})
