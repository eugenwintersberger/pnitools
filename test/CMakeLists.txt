
set(CLI_TEST_PY_FILES check_output.py
                      mcaops_test.py
                      detops_test.py)


include(${PROJECT_SOURCE_DIR}/cmake/common/BoostTestConfig.cmake)

foreach(PYFILE ${CLI_TEST_PY_FILES})
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${PYFILE}"
        ${CMAKE_CURRENT_BINARY_DIR}/${PYFILE} COPYONLY)
endforeach()

configure_file(config.hpp.in config.hpp @ONLY)

add_library(test_config OBJECT test_config.cpp command_fixture.cpp
            command_runner.cpp)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(data)
add_subdirectory(unittests)
add_subdirectory(detinfo)
add_subdirectory(nxtee)
if(NOT CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    add_subdirectory(mcaops)
endif()
add_subdirectory(datgen)
add_subdirectory(xml2nx)
add_subdirectory(nxls)
add_subdirectory(nxcat)
add_subdirectory(logs)
