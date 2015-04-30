set(COMMON_SOURCES 
                   config_utils.cpp 
                   exceptions.cpp
                   file.cpp 
                   file_utils.cpp
                   string_utils.cpp
                   image_utils.cpp
                   )

add_library(common_objects STATIC ${COMMON_SOURCES})
