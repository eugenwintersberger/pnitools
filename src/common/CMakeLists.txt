set(COMMON_SOURCES array_utils.cpp config_utils.cpp exceptions.cpp
                   file.cpp file_utils.cpp string_utils.cpp)

add_library(common_objects STATIC ${COMMON_SOURCES})
