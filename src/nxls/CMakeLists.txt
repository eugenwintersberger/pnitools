file(GLOB NXLS_SOURCE *.cpp)

add_executable(nxls ${NXLS_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(nxls ${PNIIO_PKG_LIBRARIES})
install(TARGETS nxls DESTINATION ${CMAKE_INSTALL_BINDIR})
