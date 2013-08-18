file(GLOB DET2NX_SOURCE *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(det2nx ${DET2NX_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(det2nx ${PNIIO_PKG_LIBRARIES})
