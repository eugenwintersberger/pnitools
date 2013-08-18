file(GLOB NXTEE_SOURCE *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(nxtee ${NXTEE_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(nxtee ${PNIIO_PKG_LIBRARIES})
