
configure_file(readme.txt readme.txt COPYONLY)
configure_file(download.sh download.sh COPYONLY)

set(WORKING_DIR ${PROJECT_BINARY_DIR}/test/data)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/test/data)

if(NOT EXISTS ${WORKING_DIR}/cbf)
    message(STATUS "Extracting CBF test data ...")
    execute_process(
        COMMAND ${CMAKE_COMMMAND} -E tar xzf ${SOURCE_DIR}/cbf.tar.gz
        WORKING_DIRECTORY ${WORKING_DIR}
        OUTPUT_FILE cbf_extract.log
        ERROR_FILE cbf_extract.log)
endif()

if(NOT EXISTS ${WORKING_DIR}/nexus)
    message(STATUS "Extracting NeXus test data ...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${SOURCE_DIR}/nexus.tar.gz
        WORKING_DIRECTORY ${WORKING_DIR}
        OUTPUT_FILE nexus_extract.log
        ERROR_FILE nexus_extract.log
        )
endif()

if(NOT EXISTS ${WORKING_DIR}/fio)
    message(STATUS "Extracting FIO test data ...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${SOURCE_DIR}/fio.tar.gz
        WORKING_DIRECTORY ${WORKING_DIR}
        OUTPUT_FILE fio_extract.log
        ERROR_FILE fio_extract.log
        )

endif()

if(NOT EXISTS ${WORKING_DIR}/tif)
    message(STATUS "Extracting TIF test data ...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${SOURCE_DIR}/tif.tar.gz
        WORKING_DIRECTORY ${WORKING_DIR}
        OUTPUT_FILE tif_extract.log
        ERROR_FILE tif_extract.log
        )
endif()
