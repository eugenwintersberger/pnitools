file(GLOB MCAOPS_SOURCE *.cpp)

add_executable(mcaops ${MCAOPS_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(mcaops ${PNIIO_PKG_LIBRARIES})
install(TARGETS mcaops DESTINATION ${CMAKE_INSTALL_BINDIR})
