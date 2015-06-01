set(SOURCES string_utils_test.cpp)


add_executable(common_test ${SOURCES})
target_link_libraries(common_test common_objects 
                      ${PNIIO_PKG_LIBRARIES}
                      ${Boost_LIBRARIES} 
                      )
