set(DETOPS_SOURCE detview.cpp 
                  config_utils.cpp 
                  )

add_executable(detview ${DETOPS_SOURCE})
target_link_libraries(detview common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS detview DESTINATION ${CMAKE_INSTALL_BINDIR})
