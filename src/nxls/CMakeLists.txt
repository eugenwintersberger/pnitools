set(NXLS_LIB_SOURCES metadata.cpp
	                 link_metadata.cpp
	                 data_metadata.cpp
	                 attribute_metadata.cpp
	                 dataset_metadata.cpp
	                 group_metadata.cpp
	                 metadata_extractor.cpp	                 
	                 output_configuration.cpp
	                 output_record.cpp
	                 record_builder.cpp
	                 utils.cpp
	                 )
	                
add_library(nxls_static STATIC ${NXLS_LIB_SOURCES})	     
	
set(NXLS_SOURCE nxls.cpp config.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    configure_file(nxls.exe.manifest.in nxls.exe.manifest @ONLY)
    list(APPEND NXLS_SOURCE ${PROJECT_BINARY_DIR}/src/nxls/nxls.exe.manifest)
endif()

add_executable(nxls ${NXLS_SOURCE})
target_link_libraries(nxls common_objects nxls_static pniio)
install(TARGETS nxls DESTINATION ${CMAKE_INSTALL_BINDIR})
