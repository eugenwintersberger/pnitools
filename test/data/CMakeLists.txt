
configure_file(readme.txt readme.txt COPYONLY)
configure_file(download.sh download.sh COPYONLY)

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/cbf)
    exec_program(tar ${PROJECT_BINARY_DIR}/test/data
    ARGS -xzf ${PROJECT_SOURCE_DIR]/test/data/cbf.tar.gz} )
endif()

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/nexus)
    exec_program(tar ${PROJECT_BINARY_DIR}/test/data
    ARGS -xzf ${RPOJECT_SOURCE_DIR}/test/data/nexus.tar.gz)
endif()

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/fio)
    exec_program(tar ${PROJECT_BINARY_DIR}/test/data
    ARGS -xzf ${PROJECT_SOURCE_DIR}/test/data/fio.tar.gz)
endif()

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/tif)
    exec_program(tar ${PROJECT_BINARY_DIR}/test/data
    ARGS -xzf ${PROJECT_SOURCE_DIR}/test/data/tif.tar.gz)
endif()
