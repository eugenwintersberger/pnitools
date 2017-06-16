
configure_file(readme.txt readme.txt COPYONLY)
configure_file(download.sh download.sh COPYONLY)

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/cbf)
    message(STATUS "Extracting CBF test data ...")
    execute_process(
        COMMAND ${CMAKE_COMMMAND} -E tar xzf ${PROJECT_SOURCE_DIR}/test/data/cbf.tar.gz 
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/data
        OUTPUT_FILE ${PROJECT_BINARY_DIR}/test/data/cbf_extract.log
        ERROR_FILE ${PROJECT_BINARY_DIR}/test/data/cbf_extract.log)
endif()

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/nexus)
    message(STATUS "Extracting NeXus test data ...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_SOURCE_DIR}/test/data/nexus.tar.gz
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/data
        OUTPUT_FILE ${PROJECT_BINARY_DIR}/test/data/nexus_extract.log
        ERROR_FILE ${PROJECT_BINARY_DIR}/test/data/nexus_extract.log
        )
endif()

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/fio)
    message(STATUS "Extracting FIO test data ...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_SOURCE_DIR}/test/data/fio.tar.gz
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/data
        OUTPUT_FILE ${PROJECT_BINARY_DIR}/test/data/fio_extract.log
        ERROR_FILE ${PROJECT_BINARY_DIR}/test/data/fio_extract.log
        )

endif()

if(NOT EXISTS ${PROJECT_BINARY_DIR}/test/data/tif)
    message(STATUS "Extracting TIF test data ...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_SOURCE_DIR}/test/data/tif.tar.gz
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/data
        OUTPUT_FILE ${PROJECT_BINARY_DIR}/test/data/tif_extract.log
        ERROR_FILE ${PROJECT_BINARY_DIR}/test/data/tif_extract.log
        )
endif()
