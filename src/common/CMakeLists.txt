set(COMMON_SOURCES 
                   config_utils.cpp 
                   exceptions.cpp
                   file.cpp 
                   string_utils.cpp
                   image_utils.cpp
                   file_type.cpp
                   roi.cpp
                   )

add_library(common_objects STATIC ${COMMON_SOURCES})
