set(SOURCE grid_generator.cpp
           grid_generator_builder.cpp
           datgen_utils.cpp
    )


add_library(datgen_objects OBJECT ${SOURCE})
add_executable(datgen datgen.cpp $<TARGET_OBJECTS:datgen_objects>)
target_link_libraries(datgen common_objects ${PNIIO_PKG_LIBRARIES})

install(TARGETS datgen DESTINATION ${CMAKE_INSTALL_BINDIR})

