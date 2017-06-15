set(SOURCE nxtee.cpp utils.cpp operation.cpp)

add_executable(nxtee ${SOURCE})
target_link_libraries(nxtee pniio common_objects)
install(TARGETS nxtee DESTINATION ${CMAKE_INSTALL_BINDIR})
