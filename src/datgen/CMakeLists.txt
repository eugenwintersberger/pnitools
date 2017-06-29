set(SOURCE grid_generator.cpp
           grid_generator_builder.cpp
           datgen_utils.cpp
           options_splitter.cpp
    )

set(BIN_SOURCE datgen.cpp)

add_subdirectory(functors)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    configure_file(datgen.exe.manifest.in datgen.exe.manifest @ONLY)
    list(APPEND BIN_SOURCE ${PROJECT_BINARY_DIR}/src/datgen/datgen.exe.manifest)
endif()

add_library(datgen_objects OBJECT ${SOURCE} )
add_executable(datgen ${BIN_SOURCE} $<TARGET_OBJECTS:datgen_objects>
                                 $<TARGET_OBJECTS:datgen_functor_objects>)
target_link_libraries(datgen common_objects pniio)

install(TARGETS datgen DESTINATION ${CMAKE_INSTALL_BINDIR})
