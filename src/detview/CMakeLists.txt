set(DETOPS_SOURCE detview.cpp 
                  config_utils.cpp 
                  plot.cpp
                  )
include(FindQt4)

find_package(Qt4 REQUIRED QtCore QtGui)

include_directories(${QT_INCLUDE_DIR})
add_executable(detview ${DETOPS_SOURCE})
target_link_libraries(detview common_objects 
                              ${PNIIO_PKG_LIBRARIES} 
                              ${QT_LIBRARIES}
                              mgl mgl-qt)
install(TARGETS detview DESTINATION ${CMAKE_INSTALL_BINDIR})
