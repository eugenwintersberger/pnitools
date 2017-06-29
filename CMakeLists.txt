cmake_minimum_required(VERSION 3.0)
project(pnitools
        LANGUAGES CXX C
        VERSION 1.1.0)
include(CTest)
set(CMAKE_CXX_STANDARD 11)

#==============================================================================
# load some default configuration
#==============================================================================
include(cmake/common/EnsureBuildType.cmake)
include(cmake/common/InstallConfig.cmake)
include(cmake/common/WindowsUtils.cmake)


set(WITH_CONAN OFF CACHE BOOL "Satisfy depdencies from conan")
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set(WITH_CONAN ON)
endif()

if(WITH_CONAN)

    include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

#======================do here some setup work=================================
include(configure/CMakeLists.txt)


#add_subdirectory("doc")
add_subdirectory("src/common")
add_subdirectory("src/detinfo")
add_subdirectory("src/detops")
if(NOT CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    add_subdirectory("src/mcaops")
endif()
#add_subdirectory("src/nx2xml")
add_subdirectory("src/nxcat")
add_subdirectory("src/nxls")
add_subdirectory("src/nxtee")
add_subdirectory("src/xml2nx")
add_subdirectory("src/datgen")

add_subdirectory("test")

#=============================================================================
# generate package here
#=============================================================================
if(CMAKE_HOST_SYSTEM MATCHES Windows)
    MESSAGE(STATUS "================setting up packaging====================")

    set(ASSEMBLY_DIR "desy.fsec.pnitools")
    set(ASSEMBLY_MANIFEST "desy.fsec.pnitools.manifest")

    #first we need to locate all the library files
    install(DIRECTORY ${PROJECT_BINARY_DIR}/bin/${ASSEMBLY_DIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
            PATTERN "*.exe" EXCLUDE
            PATTERN "*"
            )
        configure_file(desy.fsec.pnitools.manifest.in bin/${ASSEMBLY_DIR}/${ASSEMBLY_MANIFEST}
            @ONLY)
        install(FILES ${PROJECT_BINARY_DIR}/bin/${ASSEMBLY_DIR}/${ASSEMBLY_MANIFEST}
            DESTINATION ${CMAKE_INSTALL_BINDIR}/${ASSEMBLY_DIR}
            )

endif()
