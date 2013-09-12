file(GLOB DET2NX_SOURCE *.cpp)

add_executable(det2nx ${DET2NX_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(det2nx ${PNIIO_PKG_LIBRARIES})
install(TARGETS det2nx DESTINATION "${CMAKE_INSTALL_BINDIR}")
