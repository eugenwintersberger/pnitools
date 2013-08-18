file(GLOB NXSH_SOURCE *.cpp)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_executable(nxsh ${NXSH_SOURCE} $<TARGET_OBJECTS:common_objects>)
target_link_libraries(nxsh readline ${PNIIO_PKG_LIBRARIES})
