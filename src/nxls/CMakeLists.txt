set(NXLS_SOURCE nxls.cpp 
                config.cpp 
                utils.cpp
                output_config.cpp 
                )

add_executable(nxls ${NXLS_SOURCE})
target_link_libraries(nxls common_objects ${PNIIO_PKG_LIBRARIES})
install(TARGETS nxls DESTINATION ${CMAKE_INSTALL_BINDIR})
