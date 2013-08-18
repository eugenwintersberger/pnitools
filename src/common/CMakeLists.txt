file(GLOB COMMON_SOURCES *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_library(common_objects OBJECT ${COMMON_SOURCES})
