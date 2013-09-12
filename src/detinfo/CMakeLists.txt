file(GLOB DETINFO_SOURCE *.cpp)

add_executable(detinfo ${DETINFO_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(detinfo ${PNIIO_PKG_LIBRARIES})
install(TARGETS detinfo DESTINATION ${CMAKE_INSTALL_BINDIR})
