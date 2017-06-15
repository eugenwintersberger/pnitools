set(DETOPS_SOURCE detops.cpp
                  config.cpp
                  io_utils.cpp
                  roi_utils.cpp
                  image_processor.cpp
                  integrate.cpp
                  maximum.cpp
                  minimum.cpp
                  image_op_base.cpp
                  )

add_executable(detops ${DETOPS_SOURCE})
target_link_libraries(detops common_objects pniio)
install(TARGETS detops DESTINATION ${CMAKE_INSTALL_BINDIR})
