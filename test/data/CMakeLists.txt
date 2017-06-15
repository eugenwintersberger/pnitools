
configure_file(readme.txt readme.txt COPYONLY)
configure_file(download.sh download.sh COPYONLY)

if((NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/cbf) OR
   (NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/fio) OR
   (NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/nexus) OR
   (NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/tif))

   exec_program(tar ${PROJECT_BINARY_DIR}/test/data
   ARGS -xzf ${PROJECT_SOURCE_DIR}/test/data/test_data.tar.gz)

endif()
