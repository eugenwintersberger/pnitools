set(SOURCE grid_generator.cpp)


add_library(datgen_objects OBJECT ${SOURCE})
add_executable(datgen datgen.cpp $<TARGET_OBJECTS:datgen_objects>)
target_link_libraries(datgen common_objects)

install(TARGETS datgen DESTINATION ${CMAKE_INSTALL_BINDIR})

