
configure_file(readme.txt readme.txt COPYONLY)
configure_file(download.sh download.sh COPYONLY)

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/cbf)
    message(STATUS "Extracting CBF test data ...")
    exec_program(tar ${PROJECT_BINARY_DIR}/test/data
    ARGS -xzf ${PROJECT_SOURCE_DIR}/test/data/cbf.tar.gz )
endif()

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/nexus)
    message(STATUS "Extracting NeXus test data ...")
    exec_program(tar ${PROJECT_BINARY_DIR}/test/data
    ARGS -xzf ${PROJECT_SOURCE_DIR}/test/data/nexus.tar.gz)
endif()

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/fio)
    message(STATUS "Extracting FIO test data ...")
    exec_program(tar ${PROJECT_BINARY_DIR}/test/data
    ARGS -xzf ${PROJECT_SOURCE_DIR}/test/data/fio.tar.gz)
endif()

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/tif)
    message(STATUS "Extracting TIF test data ...")
    exec_program(tar ${PROJECT_BINARY_DIR}/test/data
    ARGS -xzf ${PROJECT_SOURCE_DIR}/test/data/tif.tar.gz)
endif()
