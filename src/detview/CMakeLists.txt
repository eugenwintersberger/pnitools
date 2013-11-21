set(DETOPS_SOURCE detview.cpp 
                  config_utils.cpp 
                  plot.cpp
                  )

#need to add the plplot library
pkg_search_module(PLPLOT REQUIRED plplotd-c++)


add_executable(detview ${DETOPS_SOURCE})
target_link_libraries(detview common_objects 
                              ${PNIIO_PKG_LIBRARIES} 
                              ${PLPLOT_LIBRARIES})
install(TARGETS detview DESTINATION ${CMAKE_INSTALL_BINDIR})
